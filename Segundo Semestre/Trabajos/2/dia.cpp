#include <bits/stdc++.h>
using namespace std;

/* ========= util PPM ========= */
struct RGB { unsigned char r,g,b; };

struct Image {
    int W,H;
    vector<RGB> pix;
    Image(int w,int h, RGB bg={255,255,255}):W(w),H(h),pix(w*h,bg){}
    inline bool in(int x,int y) const { return x>=0 && x<W && y>=0 && y<H; }
    inline void set(int x,int y, RGB c){
        if(in(x,y)) pix[y*W + x] = c;
    }
    // mezclar color (simple alpha 0..1)
    inline void blend(int x,int y, RGB c, float a){
        if(!in(x,y)) return;
        RGB p = pix[y*W+x];
        auto lerp=[&](unsigned char s,unsigned char d){ return (unsigned char)(d*(1-a)+s*a+0.5f); };
        pix[y*W+x] = { lerp(c.r,p.r), lerp(c.g,p.g), lerp(c.b,p.b) };
    }
    void save(const string& name){
        ofstream f(name, ios::binary);
        f << "P6\n" << W << " " << H << "\n255\n";
        f.write(reinterpret_cast<char*>(pix.data()), pix.size()*3);
    }
};

/* ========= dibujo primitivo ========= */
void lineBresenham(Image& im, int x0,int y0,int x1,int y1, RGB c){
    int dx = abs(x1-x0), dy = -abs(y1-y0);
    int sx = x0<x1?1:-1, sy = y0<y1?1:-1;
    int err = dx + dy;
    while(true){
        im.set(x0,y0,c);
        if(x0==x1 && y0==y1) break;
        int e2 = 2*err;
        if(e2 >= dy){ err += dy; x0 += sx; }
        if(e2 <= dx){ err += dx; y0 += sy; }
    }
}
void thickLine(Image& im, int x0,int y0,int x1,int y1, RGB c, int t=2){
    // dibuja varias líneas paralelas para “engrosar”
    if(abs(y1-y0) > abs(x1-x0)){
        for(int o=-t; o<=t; ++o) lineBresenham(im, x0+o,y0, x1+o,y1, c);
    }else{
        for(int o=-t; o<=t; ++o) lineBresenham(im, x0,y0+o, x1,y1+o, c);
    }
}
void circleFilled(Image& im, int cx,int cy,int r, RGB fill, RGB border, int border_px=1){
    int r2=r*r;
    for(int y=-r; y<=r; ++y){
        for(int x=-r; x<=r; ++x){
            int d=x*x+y*y;
            if(d<=r2){
                // borde
                if(d >= (r-border_px)*(r-border_px)) im.set(cx+x,cy+y,border);
                else im.set(cx+x,cy+y,fill);
            }
        }
    }
}
void rectFilled(Image& im, int x0,int y0,int x1,int y1, RGB c){
    if(x0>x1) swap(x0,x1); if(y0>y1) swap(y0,y1);
    for(int y=y0;y<=y1;++y) for(int x=x0;x<=x1;++x) im.set(x,y,c);
}

/* ========= mapa logístico ========= */
int main(){
    // --- Parámetros (puedes cambiarlos al ejecutar) ---
    double r, x0; int N;
    cout << "r (ej. 3.2): "; if(!(cin>>r)) return 0;
    cout << "x0 en [0,1] (ej. 0.5): "; cin >> x0;
    cout << "iteraciones (ej. 60): "; cin >> N;

    // --- Generar órbita ---
    vector<double> x; x.reserve(N+1);
    double xv = x0; x.push_back(xv);
    for(int i=0;i<N;i++){ xv = r*xv*(1.0 - xv); x.push_back(xv); }

    // --- Lienzo ---
    const int W=1200, H=520;
    Image im(W,H, {255,255,255}); // fondo blanco

    // Área de plot con márgenes
    const int L=80, R=40, T=40, B=60;
    const int PW = W - L - R;
    const int PH = H - T - B;

    // fondo del plot (ligeramente gris muy claro)
    rectFilled(im, L, T, L+PW, T+PH, {248,248,248});

    // rejilla
    RGB grid = {220,220,220};
    // horizontal (x ∈ [0,1] cada 0.1)
    for(int k=0;k<=10;k++){
        int y = T + (int)round((1.0 - k/10.0) * PH);
        thickLine(im, L, y, L+PW, y, grid, 0);
    }
    // vertical (cada 5 iteraciones aprox)
    int step = max(1, N/12);
    for(int i=0;i<=N;i+=step){
        int xpix = L + (int)round( (double)i / max(1,N) * PW );
        thickLine(im, xpix, T, xpix, T+PH, grid, 0);
    }

    // ejes
    RGB axis={120,120,120};
    thickLine(im, L, T+PH, L+PW, T+PH, axis, 1); // eje x
    thickLine(im, L, T, L, T+PH, axis, 1);       // eje y

    // curva (línea + puntos)
    RGB lineCol = {40,90,255};     // azul
    RGB ptFill  = {20,160,90};     // verde
    RGB ptEdge  = {10,100,60};     // borde oscuro

    auto XtoPix = [&](int i){
        return L + (int)round( (double)i / max(1,N) * PW );
    };
    auto YtoPix = [&](double xv){
        if(xv<0) xv=0; if(xv>1) xv=1;
        return T + (int)round( (1.0 - xv) * PH );
    };

    // línea conectando puntos
    for(int i=0;i<(int)x.size()-1;i++){
        int x0p=XtoPix(i),   y0p=YtoPix(x[i]);
        int x1p=XtoPix(i+1), y1p=YtoPix(x[i+1]);
        thickLine(im, x0p,y0p, x1p,y1p, lineCol, 1);
    }
    // puntos como círculos
    for(int i=0;i<(int)x.size();i++){
        int xp=XtoPix(i), yp=YtoPix(x[i]);
        circleFilled(im, xp, yp, 4, ptFill, ptEdge, 1);
    }

    // guardar
    im.save("orbita.ppm");
    cout << "Imagen creada: orbita.ppm\n"
         << "Ábrela con cualquier visor (GIMP, IrfanView, etc.).\n";
    return 0;
}
