#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool isValidRoll(int roll) {
    return roll >= 0 && roll <= 10;
}

int calculateScore(const vector<int>& rolls, vector<int>& frameScores) {
    int score = 0;
    int rollIndex = 0;

    for (int frame = 0; frame < 10; ++frame) {
        if (rolls[rollIndex] == 10) {  // Strike
            int frameScore = 10 + rolls[rollIndex + 1] + rolls[rollIndex + 2];
            score += frameScore;
            frameScores.push_back(score);
            rollIndex += 1;
        } else if (rolls[rollIndex] + rolls[rollIndex + 1] == 10) {  // Spare
            int frameScore = 10 + rolls[rollIndex + 2];
            score += frameScore;
            frameScores.push_back(score);
            rollIndex += 2;
        } else {  // Open frame
            int frameScore = rolls[rollIndex] + rolls[rollIndex + 1];
            score += frameScore;
            frameScores.push_back(score);
            rollIndex += 2;
        }
    }

    return score;
}

int main() {
    vector<int> rolls;
    vector<int> frameScores;
    int pins, frame = 1;

    cout << "==== Bowling Score Calculator ====\n";
    cout << "Would you like to input from file? (y/n): ";
    char inputMode;
    cin >> inputMode;

    if (inputMode == 'y' || inputMode == 'Y') {
        string filename;
        cout << "Enter input file name: ";
        cin >> filename;
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error opening file.\n";
            return 1;
        }

        int val;
        while (infile >> val) {
            rolls.push_back(val);
        }
    } else {
        while (frame <= 10) {
            if (frame < 10) {
                int roll1, roll2;
                cout << "Frame " << frame << ":\n";

                do {
                    cout << "  Roll 1: ";
                    cin >> roll1;
                } while (!isValidRoll(roll1));

                if (roll1 == 10) {
                    rolls.push_back(10);
                    frame++;
                    continue;
                }

                do {
                    cout << "  Roll 2: ";
                    cin >> roll2;
                } while (!isValidRoll(roll2) || roll1 + roll2 > 10);

                rolls.push_back(roll1);
                rolls.push_back(roll2);
                frame++;
            } else {
                cout << "Frame 10:\n";
                int r1, r2, r3 = 0;

                do {
                    cout << "  Roll 1: ";
                    cin >> r1;
                } while (!isValidRoll(r1));
                rolls.push_back(r1);

                do {
                    cout << "  Roll 2: ";
                    cin >> r2;
                } while (!isValidRoll(r2) || (r1 != 10 && r1 + r2 > 10));
                rolls.push_back(r2);

                if (r1 == 10 || r1 + r2 == 10) {
                    do {
                        cout << "  Roll 3 (Bonus): ";
                        cin >> r3;
                    } while (!isValidRoll(r3));
                    rolls.push_back(r3);
                }
                break;
            }
        }
    }

    int totalScore = calculateScore(rolls, frameScores);

    cout << "\n==== Score Breakdown ====\n";
    for (size_t i = 0; i < frameScores.size(); ++i) {
        cout << "Frame " << i + 1 << ": " << frameScores[i] << endl;
    }

    cout << "Total Score: " << totalScore << endl;

    // Optional output to file
    cout << "\nSave result to file? (y/n): ";
    char save;
    cin >> save;

    if (save == 'y' || save == 'Y') {
        string outfileName;
        cout << "Enter output file name: ";
        cin >> outfileName;
        ofstream outfile(outfileName);
        if (!outfile) {
            cerr << "Error writing to file.\n";
            return 1;
        }
        for (size_t i = 0; i < frameScores.size(); ++i) {
            outfile << "Frame " << i + 1 << ": " << frameScores[i] << "\n";
        }
        outfile << "Total Score: " << totalScore << "\n";
        cout << "Saved to " << outfileName << endl;
    }

    return 0;
}
