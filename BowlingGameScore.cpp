#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool checkRoll(int x) {
    return x >= 0 && x <= 10;
}

int getScore(const vector<int>& r, vector<int>& scores) {
    int s = 0;
    int i = 0;

    for (int f = 0; f < 10; ++f) {
        if (r[i] == 10) {
            s += 10 + r[i+1] + r[i+2];
            scores.push_back(s);
            i += 1;
        } else if (r[i] + r[i+1] == 10) {
            s += 10 + r[i+2];
            scores.push_back(s);
            i += 2;
        } else {
            s += r[i] + r[i+1];
            scores.push_back(s);
            i += 2;
        }
    }

    return s;
}

int main() {
    vector<int> r;
    vector<int> scores;
    int f = 1;

    cout << "Bowling Game\n";
    cout << "Use file input? y/n: ";
    char mode;
    cin >> mode;

    if (mode == 'y') {
        string fn;
        cout << "Filename: ";
        cin >> fn;
        ifstream fin(fn);
        int n;
        while (fin >> n) r.push_back(n);
    } else {
        while (f <= 10) {
            int a, b, c;
            cout << "Frame " << f << endl;
            cout << "  Roll 1: ";
            cin >> a;

            while (!checkRoll(a)) {
                cout << "  Invalid. Roll 1 again: ";
                cin >> a;
            }

            if (f < 10) {
                if (a == 10) {
                    r.push_back(10);
                    f++;
                    continue;
                }
                cout << "  Roll 2: ";
                cin >> b;
                while (!checkRoll(b) || (a + b > 10)) {
                    cout << "  Invalid. Roll 2 again: ";
                    cin >> b;
                }
                r.push_back(a);
                r.push_back(b);
            } else {
                // 10th frame
                cout << "  Roll 2: ";
                cin >> b;
                r.push_back(a);
                r.push_back(b);
                if (a == 10 || a + b == 10) {
                    cout << "  Roll 3: ";
                    cin >> c;
                    r.push_back(c);
                }
            }

            f++;
        }
    }

    int total = getScore(r, scores);

    cout << "\n-- Frame Scores --\n";
    for (size_t i = 0; i < scores.size(); ++i) {
        cout << "Frame " << i+1 << ": " << scores[i] << endl;
    }

    cout << "Total: " << total << endl;

    cout << "\nSave to file? (y/n): ";
    char save;
    cin >> save;

    if (save == 'y') {
        string out;
        cout << "File name: ";
        cin >> out;
        ofstream fout(out);
        for (size_t i = 0; i < scores.size(); ++i) {
            fout << "Frame " << i+1 << ": " << scores[i] << "\n";
        }
        fout << "Total: " << total << "\n";
        cout << "Saved.\n";
    }

    return 0;
}
