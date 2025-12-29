#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

enum class Direction {
    Forward,
    Backward,
    PingPong
};

class DMXChaser {
private:
    struct Group {
        int head;
        int dir;       // +1 or -1 relative direction
        int segStart;
        int segEnd;
    };

    //input parameters
    int N;      // total number of fixtures
    int Ng;     // number of groups
    int Sg;     // fixtures per group
    int Ss;     // step size
    Direction Dir;
    int Pr;     // parity
    bool randomMotion = false;
    vector<Group> initialGroups;
    int step;

    //output parameters
    vector<vector<int>> sequence;

    void clearConsole() {
        cout << "\033[2J\033[H";
    }

    int paritySign(int g) {
        if (Pr == 0) return 1;
        int block = Pr;
        return ((g / block) % 2 == 0) ? 1 : -1;
    }

    void initializeGroups() {
        int baseDir = (Dir == Direction::Backward) ? -1 : 1;
        int segLength = N / Ng;
        initialGroups.resize(Ng);

        for (int g = 0; g < Ng; ++g) {
            int dir = baseDir * paritySign(g);
            int segStart = g * segLength;
            int segEnd = segStart + segLength - 1;

            if (dir > 0)
                initialGroups[g].head = segStart;
            else
                initialGroups[g].head = segEnd - Sg + 1;

            initialGroups[g].dir = dir;
            initialGroups[g].segStart = segStart;
            initialGroups[g].segEnd = segEnd;
        }

        step = 0;
    }

public:
    DMXChaser() : N(0), Ng(0), Sg(0), Ss(0), Dir(Direction::Forward), Pr(0), step(0) {}

    void setup(int totalFixtures, int numGroups, int groupSize, int stepSize,
               Direction dir, int parity, bool random = false) {
        N = totalFixtures;
        Ng = numGroups;
        Sg = groupSize;
        Ss = stepSize;
        Dir = dir;
        Pr = parity;
        randomMotion = random;

        initializeGroups();
    }

    vector<vector<int>> *computeVseq() {
        struct GroupRuntime { int head; int dir; int segStart; int segEnd; };
        vector<GroupRuntime> groups(Ng);

        int segLength = N / Ng;
        int baseDir = (Dir == Direction::Backward) ? -1 : 1;

        // Number of steps per group
        int NstepSingle = ((segLength - Sg) + Ss - 1) / Ss;
        int Nsteps = (Dir == Direction::PingPong) ? 2 * NstepSingle : NstepSingle+1;

        vector<vector<int>> Vseq;
        random_device rd;
        mt19937 rng(rd());

        // Prepare per-group sequences
        vector<vector<int>> groupSequences(Ng);

        for (int g = 0; g < Ng; ++g) {
            int dir = baseDir * paritySign(g);
            int segStart = g * segLength;
            int segEnd = segStart + segLength - 1;

            if (!randomMotion) {
                int head = (dir > 0) ? segStart : segEnd - Sg + 1;
                groups[g] = {head, dir, segStart, segEnd};
            } else {
                // Generate all valid positions in segment
                vector<int> positions;
                for (int pos = segStart; pos <= segEnd - Sg + 1; pos += Ss)
                    positions.push_back(pos);

                shuffle(positions.begin(), positions.end(), rng);

                // For PingPong: forward sequence
                groupSequences[g] = positions;

                if (Dir == Direction::PingPong) {
                    // Append reversed sequence for return trip
                    vector<int> rev = positions;
                    reverse(rev.begin(), rev.end());
                    groupSequences[g].insert(groupSequences[g].end(), rev.begin(), rev.end());
                }
            }
        }

        // Build sequence step by step
        for (int s = 0; s < Nsteps; ++s) {
            vector<int> Vstep;

            for (int g = 0; g < Ng; ++g) {
                int head;
                if (!randomMotion) {
                    head = groups[g].head;
                } else {
                    head = groupSequences[g][s % groupSequences[g].size()];
                }

                for (int i = 0; i < Sg; ++i) {
                    int idx = head + i;
                    if (idx >= 0 && idx < N) Vstep.push_back(idx);
                }
            }

            Vseq.push_back(Vstep);

            // Move groups (linear/PingPong)
            if (!randomMotion) {
                if (Dir == Direction::PingPong) {
                    bool bounce = false;
                    for (auto &g : groups) {
                        int nextHead = g.head + g.dir * Ss;
                        if (nextHead < g.segStart || nextHead > g.segEnd - Sg + 1)
                            bounce = true;
                    }
                    if (bounce) for (auto &g : groups) g.dir *= -1;
                    for (auto &g : groups) g.head += g.dir * Ss;
                } else {
                    for (auto &g : groups) g.head += g.dir * Ss;
                }
            }
        }

        this->sequence = Vseq;
        return &(this->sequence);
    }

    // Return number of steps until fixture i lights up after step i_step
    int steps_until(int fixtureIndex, int i_step) {
        if (sequence.empty()) computeVseq();
        int Nsteps = sequence.size();

        int start = (i_step + 1) % Nsteps;  // start searching at next step
        for (int offset = 1; offset <= Nsteps; ++offset) {
            int s = (i_step + offset) % Nsteps;
            if (find(sequence[s].begin(), sequence[s].end(), fixtureIndex) != sequence[s].end())
                return offset;
        }

        return -1; // should never happen
    }

    // Return number of steps since fixture i was last lit before step i_step
    int steps_since(int fixtureIndex, int i_step) {
        if (sequence.empty()) computeVseq();
        int Nsteps = sequence.size();
        int start = i_step % Nsteps;

        for (int offset = 0; offset < Nsteps; ++offset) {
            int s = (start - offset + Nsteps) % Nsteps; // wrap backward
            if (find(sequence[s].begin(), sequence[s].end(), fixtureIndex) != sequence[s].end())
                return offset; // number of steps since last light-up
        }
        return -1; // should never happen
    }


    void printSequence() {
        vector<vector<int>> *Vseq = computeVseq();
        int totalSteps = Vseq->size();

        int stepWidth = to_string(totalSteps - 1).length(); // max digits

        for (int s = 0; s < totalSteps; ++s) {
            vector<char> strip(N, '.');
            for (int idx : (*Vseq)[s])
                strip[idx] = '#';

            // setw(stepWidth) ensures the step number is right-aligned
            cout << "Step " << setw(stepWidth) << s << ":\t";
            for (char c : strip) cout << c;
            cout << "\n";
        }
    }
};


int main() {
    // Create chaser
    DMXChaser chaser;

    // Setup parameters
    int N = 18;         // total fixtures
    int Ng = 1;         // number of groups
    int Sg = 1;         // fixtures per group
    int Ss = 1;         // step size
    Direction Dir = Direction::Forward;
    int Pr = 0;         // parity
    bool randomMotion = false;

    chaser.setup(N, Ng, Sg, Ss, Dir, Pr, randomMotion);

    // Precompute and print sequence
    cout << "=== Full sequence ===\n";
    chaser.printSequence();

    // Example: query steps_until and steps_since
    int fixture = 3;      // fixture index
    int i_step = 0;       // current step in sequence

    int until = chaser.steps_until(fixture, i_step);
    int since = chaser.steps_since(fixture, i_step);

    cout << "\nFixture " << fixture << " at step " << i_step << ":\n";
    cout << "  Steps until next light-up: " << until << "\n";
    cout << "  Steps since last light-up: " << since << "\n";

    // Query multiple fixtures
    cout << "\nAll fixtures at step " << i_step << ":\n";
    for (int f = 0; f < N; ++f) {
        cout << "Fixture " << f << ": until=" << chaser.steps_until(f, i_step)
             << ", since=" << chaser.steps_since(f, i_step) << "\n";
    }

    return 0;
}