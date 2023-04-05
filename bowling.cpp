#include <iostream>
#include <vector>

using namespace std;

vector<int> scores (vector<char>& rolls) {
    vector<int> result(10);
    vector<int> frame_scores(10);

    
    for (int i=0; i<rolls.size(); i++) {
        if (rolls[i] == '-')
            continue;

        int curr_frame = i/2;

        if (curr_frame >= 10) {
            curr_frame = 9;
        }         

        if (rolls[i] == '/') {
            frame_scores[curr_frame] = 10;

            if (rolls[i-1] == '/') {
                // never possible
            }
            if ((i-2) > 0 && rolls[i-2] == 'X') {
                // never possible
            }

            if ((i-3) > 0 && rolls[i-3] == 'X') {
                frame_scores[(i-3)/2] += (10 - (rolls[i-1] - '0'));
            }
        }
        else if (rolls[i] == 'X') {
            frame_scores[curr_frame] = 10;
            if ((i-1) > 0 && rolls[i-1] == '/') {
                frame_scores[(i-1)/2] += 10;
            }

            if ((i-2) > 0 && rolls[i-2] == 'X') {
                frame_scores[(i-2)/2] += 10;
            }

            if ((i-3) > 0 && rolls[i-3] == 'X') {
                frame_scores[(i-3)/2] += 10;
            }

            if ((i-4) > 0 && rolls[i-4] == 'X') {
                frame_scores[(i-4)/2] += 10;
            }
        }
        else {
            int pins = rolls[i] - '0';
            frame_scores[curr_frame] += pins;

            // Bonus conditions
            if ((i-1) > 0 && rolls[i-1] == '/') {
                frame_scores[(i-1)/2] += pins;
            }
            if ((i-2) > 0 && rolls[i-2] == 'X') {
                frame_scores[(i-2)/2] += pins;
            }
            if ((i-3) > 0 && rolls[i-3] == 'X') {
                frame_scores[(i-3)/2] += pins;
            }
            if ((i-4) > 0 && rolls[i-4] == 'X') {
                frame_scores[(i-4)/2] += pins;
            }
        }

    }


    // The rules are different in last frame, using a different logic to handle this
    int lastFrameStart = (rolls.size() == 21) ? rolls.size()-3:rolls.size()-2;
    int lastFrameScore = 0;
    while (lastFrameStart < rolls.size()) {
        if (rolls[lastFrameStart] == '/') {
            lastFrameScore = 10;
        }
        else if (rolls[lastFrameStart] == 'X'){
            lastFrameScore += 10;
        } else {
            int pins = rolls[lastFrameStart] - '0';
            lastFrameScore += pins;
        }
        lastFrameStart++;
    }

    frame_scores[9] = lastFrameScore;

    result[0] = frame_scores[0];
    for (int i=1; i<frame_scores.size(); i++) {
        result[i] = result[i-1] + frame_scores[i];
    }

    cout << "Each Frame scores: ";
    for (auto z: frame_scores) {
        cout << z << " ";
    }
    cout << endl;


    cout << "Total scores: ";
    for (auto z: result) {
        cout << z << " ";
    }
    cout << endl;

    return result;

}


int main () {
    vector<char> rolls;

    rolls.push_back('1');
    rolls.push_back('4');

    rolls.push_back('4');
    rolls.push_back('5');

    rolls.push_back('6');
    rolls.push_back('/');

    rolls.push_back('5');
    rolls.push_back('/');

    rolls.push_back('X');
    rolls.push_back('-');

    rolls.push_back('0');
    rolls.push_back('1');

    rolls.push_back('7');
    rolls.push_back('/');

    rolls.push_back('6');
    rolls.push_back('/');

    rolls.push_back('X');
    rolls.push_back('-');

    rolls.push_back('2');
    rolls.push_back('/');
    rolls.push_back('6');

    vector<int> results = scores(rolls);
    return 0;
}