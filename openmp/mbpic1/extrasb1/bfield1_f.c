/* C Library for Skeleton 1-2/2D Electromagnetic PIC Code field    */
/* diagnostics                                                     */
/* Wrappers for calling the Fortran routines from a C main program */

#include <complex.h>

void potp1_(float complex *q, float complex *pot, float complex *ffc,
            float *we, int *nx, int *nxvh, int *nxhd);

void divf1_(float complex *f, float complex *df, int *nx, int *ndim,
            int *nxvh);

void gradf1_(float complex *df, float complex *f, int *nx, int *ndim,
             int *nxvh);

void curlf1_(float complex *f, float complex *g, int *nx, int *nxvh);

void avpot13_(float complex *byz, float complex *ayz, int *nx,
              int *nxvh);

void avrpot13_(float complex *ayz, float complex *byz,
               float complex *ffc, float *ci, int *nx, int *nxvh,
               int *nxhd);

void smooth1_(float complex *q, float complex *qs, float complex *ffc,
              int *nx, int *nxvh, int *nxhd);

void smooth13_(float complex *cu, float complex *cus,
               float complex *ffc, int *nx, int *nxvh, int *nxhd);

void rdmodes1_(float complex *pot, float complex *pott, int *nx,
               int *modesx, int *nxvh, int *modesxd);

void wrmodes1_(float complex *pot, float complex *pott, int *nx,
               int *modesx, int *nxvh, int *modesxd);

void rdvmodes1_(float complex *vpot, float complex *vpott, int *nx,
                int *modesx, int *ndim, int *nxvh, int *modesxd);
void wrvmodes1_(float complex *vpot, float complex *vpott, int *nx,
                int *modesx, int *ndim, int *nxvh, int *modesxd);

/* Interfaces to C */

/*--------------------------------------------------------------------*/
void cpotp1(float complex q[], float complex pot[], float complex ffc[],
            float *we, int nx, int nxvh, int nxhd) {
   potp1_(q,pot,ffc,we,&nx,&nxvh,&nxhd);
   return;
}

/*--------------------------------------------------------------------*/
void cdivf1(float complex f[], float complex df[], int nx, int ndim,
            int nxvh) {
   divf1_(f,df,&nx,&ndim,&nxvh);
   return;
}

/*--------------------------------------------------------------------*/
void cgradf1(float complex df[], float complex f[], int nx, int ndim,
             int nxvh) {
   gradf1_(df,f,&nx,&ndim,&nxvh);
   return;
}

/*--------------------------------------------------------------------*/
void ccurlf1(float complex f[], float complex g[], int nx, int nxvh) {
   curlf1_(f,g,&nx,&nxvh);
   return;
}

/*--------------------------------------------------------------------*/
void cavpot13(float complex byz[], float complex ayz[], int nx,
              int nxvh) {
   avpot13_(byz,ayz,&nx,&nxvh);
   return;
}

/*--------------------------------------------------------------------*/
void cavrpot13(float complex ayz[], float complex byz[],
               float complex ffc[], float ci, int nx, int nxvh,
               int nxhd) {
   avrpot13_(ayz,byz,ffc,&ci,&nx,&nxvh,&nxhd);
   return;
}

/*--------------------------------------------------------------------*/
void csmooth1(float complex q[], float complex qs[],
              float complex ffc[], int nx, int nxvh, int nxhd) {
   smooth1_(q,qs,ffc,&nx,&nxvh,&nxhd);
   return;
}

/*--------------------------------------------------------------------*/
void csmooth13(float complex cu[], float complex cus[], 
               float complex ffc[], int nx, int nxvh, int nxhd) {
   smooth13_(cu,cus,ffc,&nx,&nxvh,&nxhd);
   return;
}

/*--------------------------------------------------------------------*/
void crdmodes1(float complex pot[], float complex pott[], int nx,
               int modesx, int nxvh, int modesxd) {
   rdmodes1_(pot,pott,&nx,&modesx,&nxvh,&modesxd);
   return;
}

/*--------------------------------------------------------------------*/
void cwrmodes1(float complex pot[], float complex pott[], int nx,
               int modesx, int nxvh, int modesxd) {
   wrmodes1_(pot,pott,&nx,&modesx,&nxvh,&modesxd);
   return;
}

/*--------------------------------------------------------------------*/
void crdvmodes1(float complex vpot[], float complex vpott[], int nx,
                int modesx, int ndim, int nxvh, int modesxd) {
   rdvmodes1_(vpot,vpott,&nx,&modesx,&ndim,&nxvh,&modesxd);

   return;
}

/*--------------------------------------------------------------------*/
void cwrvmodes1(float complex vpot[], float complex vpott[], int nx,
                int modesx, int ndim, int nxvh, int modesxd) {
   wrvmodes1_(vpot,vpott,&nx,&modesx,&ndim,&nxvh,&modesxd);
   return;
}

