#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>

template<typename T>
using V_t = std::vector<T>;
using pos_t = std::pair<int16_t, int16_t>;

int16_t g_height, g_width;

void getEarthOffset(V_t<std::string>& vEnv, V_t<int16_t>& vEarth);
//return fall range 
int16_t  getMeteorObj(V_t<std::string>& vEnv, V_t<int16_t>& vEarth, V_t<pos_t>& vObj, pos_t sPos);
void fallDown(V_t<std::string>& vEnv, V_t<int16_t>& vEarth, V_t<pos_t>& vObj, int16_t fallRange);

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    std::cin >> g_height >> g_width;

    V_t<std::string> vEnv(g_height);
    V_t<int16_t>         vEarth(g_width);
    V_t<pos_t>       vObj;
    

    for(int16_t i=0;i<g_height;i++) {
        vEnv[i].resize(g_width+1);
        std::cin >> vEnv[i];
    }

    getEarthOffset(vEnv, vEarth);

    for(int16_t y=g_height-1;y>=0;y--) {
        for(int16_t x=0;x<g_width;x++) {
            if(vEnv[y][x] == 'X') {
                auto range = getMeteorObj( vEnv, vEarth, vObj, pos_t{y, x});
                fallDown(vEnv, vEarth, vObj, range);
            }
        }
    }

    for(int16_t y=0;y<g_height;y++) {
        for(int16_t x=0;x<g_width;x++) {
            auto ch = vEnv[y][x];
            if(ch == 'x') ch = 'X';
            std::cout << ch;
        }
        std::cout << '\n';
    }
}

void getEarthOffset(V_t<std::string>& vEnv, V_t<int16_t>& vEarth) {
    for(int16_t x=0;x<g_width;x++) {
        for(int16_t y=0;y<g_height;y++) {
            if(vEnv[y][x] == '#') {
                vEarth[x] = y;
                break;
            }
        }
    }
}

int16_t getMeteorObj(V_t<std::string>& vEnv, V_t<int16_t>& vEarth, V_t<pos_t>& vObj,pos_t sPos) {
    vObj.clear();
    static int16_t dy[] = {-1,0,1,0};
    static int16_t dx[] = {0,1,0,-1};
    static V_t<int16_t> vUnder(3000);
    std::fill(std::begin(vUnder), std::end(vUnder), -1);
    std::queue<pos_t> Q;
    Q.emplace(sPos);
    vObj.emplace_back(sPos);
    auto[sy, sx] = sPos;
    vEnv[sy][sx] = 'x';

    int16_t x_min = g_width;
    int16_t x_max = -1;

    while(!Q.empty()) {
        auto[y, x] = Q.front(); Q.pop();
        if(vUnder[x] == -1 || vUnder[x] < y) 
            vUnder[x] = y;
        x_min = std::min(x, x_min);
        x_max = std::max(x, x_max);
        for(int16_t i=0;i<4;i++) {
            int16_t ny = y + int16_t(dy[i]);
            int16_t nx = x + int16_t(dx[i]);
            if(ny < 0 || ny >= g_height || nx < 0 || nx >= g_width) continue;
            if(vEnv[ny][nx] == 'X') {
                Q.emplace(ny, nx);
                vObj.emplace_back(ny, nx);
                vEnv[ny][nx] = 'x';
            } 
        }
    }
    int16_t ret = g_height;
    for(int16_t x=x_min;x<=x_max;x++) {
        auto u = vUnder[x];
        int16_t range = vEarth[x] - u - 1;
        ret = std::min(ret, range);
    }
    return ret;
}

void fallDown(V_t<std::string>& vEnv, V_t<int16_t>& vEarth, V_t<pos_t>& vObj, int16_t fallRange) {
    for(auto& p:vObj) {
        auto[y, x] = p;
        vEnv[y][x] = '.';
        int16_t ny = y + fallRange;
        vEnv[ny][x] = 'x';
        vEarth[x] = std::min(vEarth[x], ny);
    }
}