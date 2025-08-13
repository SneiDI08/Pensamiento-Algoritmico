#include <iostream>
#include <vector>
using namespace std;

class neurona {
private:
    vector<int> w;
    int umbral;
    
public:
    neurona(const vector<int> we, int t) : w(we), umbral(t) {}
    
    int computeOutput(const vector<int>& inputs) {
        if (inputs.size() != w.size()) {
            cerr << "Error - Size problem";
            return -1;
        }
        int sum = 0;
        for (size_t i = 0; i < inputs.size(); ++i) {
            sum += inputs[i] * w[i];
        }
        return sum >= umbral ? 1 : 0;
    }
};

void yqk() {
    vector<int> w = {1, 1};
    int umbral = 2;
    neurona y(w, umbral);
    
    vector<vector<int>> test = {{0,0},{0,1},{1,0},{1,1}};
    for (const auto& i : test) {
        cout << i[0] << " " << i[1] << " = " << y.computeOutput(i) << endl;
    }
}

void oqk() {
    vector<int> w = {1, 1};
    int umbral = 1;
    neurona o(w, umbral);
    
    vector<vector<int>> test = {{0,0},{0,1},{1,0},{1,1}};
    for (const auto& i : test) {
        cout << i[0] << " " << i[1] << " = " << o.computeOutput(i) << endl;
    }
}

void norqk() {
    vector<int> w = {-1, -1};
    int umbral = -1;
    neurona n(w, umbral);
    
    vector<vector<int>> test = {{0,0},{0,1},{1,0},{1,1}};
    for (const auto& i : test) {
        cout << i[0] << " " << i[1] << " = " << n.computeOutput(i) << endl;
    }
}

void nandqk() {
    vector<int> w = {-1, -1};
    int umbral = -2;
    neurona n(w, umbral);
    
    vector<vector<int>> test = {{0,0},{0,1},{1,0},{1,1}};
    for (const auto& i : test) {
        cout << i[0] << " " << i[1] << " = " << n.computeOutput(i) << endl;
    }
}

void notqk() {
    vector<int> w = {-1};
    int umbral = 0;
    neurona n(w, umbral);
    
    vector<vector<int>> test = {{0},{1}};
    for (const auto& i : test) {
        cout << i[0] << " = " << n.computeOutput(i) << endl;
    }
}

void xorqk() {
    neurona and_gate({1, 1}, 2);
    neurona or_gate({1, 1}, 1);
    neurona and_not_gate({1, -1}, 1);
    
    vector<vector<int>> test = {{0,0},{0,1},{1,0},{1,1}};
    for (const auto& i : test) {
        int out_and = and_gate.computeOutput(i);
        int out_or = or_gate.computeOutput(i);
        int out_xor = and_not_gate.computeOutput({out_or, out_and});
        cout << i[0] << " " << i[1] << " = " << out_xor << endl;
    }
}

void xnorqk() {
    neurona and_gate({1, 1}, 2);
    neurona or_gate({1, 1}, 1);
    neurona and_not_gate({1, -1}, 1);
    neurona not_gate({-1}, 0);
    
    vector<vector<int>> test = {{0,0},{0,1},{1,0},{1,1}};
    for (const auto& i : test) {
        int out_and = and_gate.computeOutput(i);
        int out_or = or_gate.computeOutput(i);
        int out_xor = and_not_gate.computeOutput({out_or, out_and});
        int out_xnor = not_gate.computeOutput({out_xor});
        cout << i[0] << " " << i[1] << " = " << out_xnor << endl;
    }
}

int main() {
    cout << "### AND ###" << endl;
    yqk();
    cout << "\n### OR ###" << endl;
    oqk();
    cout << "\n### NOR ###" << endl;
    norqk();
    cout << "\n### NAND ###" << endl;
    nandqk();
    cout << "\n### NOT ###" << endl;
    notqk();
    cout << "\n### XOR ###" << endl;
    xorqk();
    cout << "\n### XNOR ###" << endl;
    xnorqk();
    
    return 0;
}
