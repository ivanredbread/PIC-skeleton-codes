/* C Library for Skeleton 3D Electromagnetic MPI PIC Code */
/* Wrappers for calling the Fortran routines from a C main program */

#include <complex.h>
#include "pbpush3.h"

double ranorm_();

void pdicomp32l_(float *edges, int *nyzp, int *noff, int *nypmx,
                 int *nzpmx, int *nypmn, int *nzpmn, int *ny, int *nz,
                 int *kstrt, int *nvpy, int *nvpz, int *idps,
                 int *idds);

void fcomp32_(int *nvp, int *nx, int *ny, int *nz, int *nvpy, int *nvpz,
              int *ierr);

void pdistr32_(float *part, float *edges, int *npp, int *nps,
               float *vtx, float *vty, float *vtz, float *vdx,
               float *vdy, float *vdz, int *npx, int *npy, int *npz,
               int *nx, int *ny, int *nz, int *idimp, int *npmax,
               int *idps, int *ipbc, int *ierr);

void ppgbpush32l_(float *part, float *fxyz, float *bxyz, float *edges,
                  int *npp, int *noff, int *ihole, float *qbm,
                  float *dt, float *dtc, float *ek, int *nx, int *ny,
                  int *nz, int *idimp, int *npmax, int *nxv, int *nypmx,
                  int *nzpmx, int *idps, int *idds, int *ntmax,
                  int *ipbc);

void ppgrbpush32l_(float *part, float *fxyz, float *bxyz, float *edges,
                   int *npp, int *noff, int *ihole, float *qbm,
                   float *dt, float *dtc, float *ci, float *ek, int *nx,
                   int *ny, int *nz, int *idimp, int *npmax, int *nxv,
                   int *nypmx, int *nzpmx, int *idps, int *idds,
                   int *ntmax, int *ipbc);

void ppgpost32l_(float *part, float *q, int *npp, int *noff, float *qm,
                 int *idimp, int *npmax, int *nxv, int *nypmx,
                 int *nzpmx, int *idds);

void ppgjpost32l_(float *part, float *cu, float *edges, int *npp,
                  int *noff, int *ihole, float *qm, float *dt, int *nx,
                  int *ny, int *nz, int *idimp, int *npmax, int *nxv,
                  int *nypmx, int *nzpmx, int *idps, int *idds,
                  int *ntmax, int *ipbc);

void ppgrjpost32l_(float *part, float *cu, float *edges, int *npp,
                   int *noff, int *ihole, float *qm, float *dt,
                   float *ci, int *nx, int *ny, int *nz, int *idimp,
                   int *npmax, int *nxv, int *nypmx, int *nzpmx,
                   int *idps, int *idds, int *ntmax, int *ipbc);

void ppdsortp32yzl_(float *parta, float *partb, int *npic, int *npp,
                    int *noff, int *nyzp, int *idimp, int *npmax,
                    int *nyzpm1, int *idds);

void ppcguard32xl_(float *fxyz, int *nyzp, int *nx, int *ndim, int *nxe,
                   int *nypmx, int *nzpmx, int *idds);

void ppaguard32xl_(float *q, int *nyzp, int *nx, int *nxe, int *nypmx,
                   int *nzpmx, int *idds);

void ppacguard32xl_(float *cu, int *nyzp, int *nx, int *ndim, int *nxe,
                    int *nypmx, int *nzpmx, int *idds);

void ppois332_(float complex *q, float complex *fxyz, int *isign,
               float complex *ffc, float *ax, float *ay, float *az,
               float *affp, float *we, int *nx, int *ny, int *nz,
               int *kstrt, int *nvpy, int *nvpz, int *nzv, int *kxyp,
               int *kyzp, int *nzhd);

void ppcuperp32_(float complex *cu, int *nx, int *ny, int *nz,
                 int *kstrt, int *nvpy, int *nvpz, int *nzv, int *kxyp,
                 int *kyzp);

void ippbpoisp332_(float complex *cu, float complex *bxyz,
                   float complex *ffc, float *ci, float *wm, int *nx,
                   int *ny, int *nz, int *kstrt, int *nvpy, int *nvpz,
                   int *nzv, int *kxyp, int *kyzp, int *nzhd);

void ppmaxwel32_(float complex *exyz, float complex *bxyz,
                 float complex *cu, float complex *ffc, float *affp,
                 float *ci, float *dt, float *wf, float *wm, int *nx,
                 int *ny, int *nz, int *kstrt, int *nvpy, int *nvpz,
                 int *nzv, int *kxyp, int *kyzp, int *nzhd);

void ppemfield32_(float complex *fxyz, float complex *exyz,
                  float complex *ffc, int *isign, int *nx, int *ny,
                  int *nz, int *kstrt, int *nvpy, int *nvpz, int *nzv,
                  int *kxyp, int *kyzp, int *nzhd);

void wpfft32rinit_(int *mixup, float complex *sct, int *indx, int *indy,
                   int *indz, int *nxhyzd, int *nxyzhd);

void ppfft32rxx_(float complex *f, int *isign, int *mixup,
                 float complex *sct, int *indx, int *indy, int *indz,
                 int *kstrt, int *nvp, int *kypi, int *kypp, int *nxvh,
                 int *kzpp, int *kypd, int *kzpd, int *nxhyzd,
                 int *nxyzhd);

void ppfft32rxy_(float complex *g, int *isign, int *mixup,
                 float complex *sct, int *indx, int *indy, int *indz,
                 int *kstrt, int *nvpy, int *nvpz, int *kxypi,
                 int *kxypp, int *nyv, int *kzpp, int *kxypd, int *kzpd,
                 int *nxhyzd, int *nxyzhd);

void ppfft32rxz_(float complex *h, int *isign, int *mixup,
                 float complex *sct, int *indx, int *indy, int *indz,
                 int *kstrt, int *nvpy, int *nvpz, int *kxypi,
                 int *kxypp, int *nzv, int *kyzp, int *kxypd,
                 int *kyzpd, int *nxhyzd, int *nxyzhd);

void ppfft32r3xx_(float complex *f, int *isign, int *mixup,
                  float complex *sct, int *indx, int *indy, int *indz,
                  int *kstrt, int *nvp, int *kypi, int *kypp, int *nxvh,
                  int *kzpp, int *kypd, int *kzpd, int *nxhyzd,
                  int *nxyzhd);

void ppfft32r3xy_(float complex *g, int *isign, int *mixup,
                  float complex *sct, int *indx, int *indy, int *indz,
                  int *kstrt, int *nvpy, int *nvpz, int *kxypi,
                  int *kxypp, int *nyv, int *kzpp, int *kxypd, 
                  int *kzpd, int *nxhyzd, int *nxyzhd);

void ppfft32r3xz_(float complex *h, int *isign, int *mixup,
                  float complex *sct, int *indx, int *indy, int *indz,
                  int *kstrt, int *nvpy, int *nvpz, int *kxypi,
                  int *kxypp, int *nzv, int *kyzp, int *kxypd, 
                  int *kyzpd, int *nxhyzd, int *nxyzhd);

void wppfft32r_(float complex *f, float complex *g, float complex *h,
                float complex *bs, float complex *br, int *isign,
                int *ntpose, int *mixup, float complex *sct,
                float *ttp, int *indx, int *indy, int *indz, int *kstrt,
                int *nvpy, int *nvpz, int *nxvh, int *nyv, int *nzv,
                int *kxyp, int *kyp, int *kyzp, int *kzp, int *kxypd,
                int *kypd, int *kyzpd, int *kzpd, int *kzyp,
                int *nxhyzd, int *nxyzhd);

void wppfft32r3_(float complex *f, float complex *g, float complex *h,
                 float complex *bs, float complex *br, int *isign,
                 int *ntpose, int *mixup, float complex *sct,
                 float *ttp, int *indx, int *indy, int *indz,
                 int *kstrt, int *nvpy, int *nvpz, int *nxvh, int *nyv,
                 int *nzv, int *kxyp, int *kyp, int *kyzp, int *kzp,
                 int *kxypd, int *kypd, int *kyzpd, int *kzpd,
                 int *kzyp, int *nxhyzd, int *nxyzhd);

/* Interfaces to C */

double ranorm() {
  return ranorm_();
}

/*--------------------------------------------------------------------*/
void cpdicomp32l(float edges[], int nyzp[], int noff[], int *nypmx,
                 int *nzpmx, int *nypmn, int *nzpmn, int ny, int nz,
                 int kstrt, int nvpy, int nvpz, int idps, int idds) {
   pdicomp32l_(edges,nyzp,noff,nypmx,nzpmx,nypmn,nzpmn,&ny,&nz,&kstrt,
               &nvpy,&nvpz,&idps,&idds);
   return;
}

/*--------------------------------------------------------------------*/
void cfcomp32(int nvp, int nx, int ny, int nz, int *nvpy, int *nvpz,
              int *ierr) {
   fcomp32_(&nvp,&nx,&ny,&nz,nvpy,nvpz,ierr);
   return;
}

/*--------------------------------------------------------------------*/
void cpdistr32(float part[], float edges[], int *npp, int nps,
               float vtx, float vty, float vtz, float vdx, float vdy,
               float vdz, int npx, int npy, int npz, int nx, int ny,
               int nz, int idimp, int npmax, int idps, int ipbc,
               int *ierr) {
   pdistr32_(part,edges,npp,&nps,&vtx,&vty,&vtz,&vdx,&vdy,&vdz,&npx,
             &npy,&npz,&nx,&ny,&nz,&idimp,&npmax,&idps,&ipbc,ierr);
   return;
}

/*--------------------------------------------------------------------*/
void cppgbpush32l(float part[], float fxyz[], float bxyz[],
                  float edges[], int npp, int noff[], int ihole[],
                  float qbm, float dt, float dtc, float *ek, int nx,
                  int ny, int nz, int idimp, int npmax, int nxv,
                  int nypmx, int nzpmx, int idps, int idds, int ntmax,
                  int ipbc) {
   ppgbpush32l_(part,fxyz,bxyz,edges,&npp,noff,ihole,&qbm,&dt,&dtc,ek,
                &nx,&ny,&nz,&idimp,&npmax,&nxv,&nypmx,&nzpmx,&idps,
                &idds,&ntmax,&ipbc);
   return;
}

/*--------------------------------------------------------------------*/
void cppgrbpush32l(float part[], float fxyz[], float bxyz[],
                   float edges[], int npp, int noff[], int ihole[],
                   float qbm, float dt, float dtc, float ci, float *ek,
                   int nx, int ny, int nz, int idimp, int npmax, 
                   int nxv, int nypmx, int nzpmx, int idps, int idds,
                   int ntmax, int ipbc) {
   ppgrbpush32l_(part,fxyz,bxyz,edges,&npp,noff,ihole,&qbm,&dt,&dtc,&ci,
                 ek,&nx,&ny,&nz,&idimp,&npmax,&nxv,&nypmx,&nzpmx,&idps,
                 &idds,&ntmax,&ipbc);
   return;
}

/*--------------------------------------------------------------------*/
void cppgpost32l(float part[], float q[], int npp, int noff[], float qm,
                 int idimp, int npmax, int nxv, int nypmx, int nzpmx,
                 int idds) {
   ppgpost32l_(part,q,&npp,noff,&qm,&idimp,&npmax,&nxv,&nypmx,&nzpmx,
               &idds);
   return;
}

/*--------------------------------------------------------------------*/
void cppgjpost32l(float part[], float cu[], float edges[], int npp,
                  int noff[], int ihole[], float qm, float dt, int nx,
                  int ny, int nz, int idimp, int npmax, int nxv,
                  int nypmx, int nzpmx, int idps, int idds, int ntmax,
                  int ipbc) {
   ppgjpost32l_(part,cu,edges,&npp,noff,ihole,&qm,&dt,&nx,&ny,&nz,
                &idimp,&npmax,&nxv,&nypmx,&nzpmx,&idps,&idds,&ntmax,
                &ipbc);
   return;
}

/*--------------------------------------------------------------------*/
void cppgrjpost32l(float part[], float cu[], float edges[], int npp,
                   int noff[], int ihole[], float qm, float dt,
                   float ci, int nx, int ny, int nz, int idimp,
                   int npmax, int nxv, int nypmx, int nzpmx, int idps,
                   int idds, int ntmax, int ipbc) {
   ppgrjpost32l_(part,cu,edges,&npp,noff,ihole,&qm,&dt,&ci,&nx,&ny,&nz,
                 &idimp,&npmax,&nxv,&nypmx,&nzpmx,&idps,&idds,&ntmax,
                 &ipbc);
   return;
}

/*--------------------------------------------------------------------*/
void cppdsortp32yzl(float parta[], float partb[], int npic[], int npp,
                    int noff[], int nyzp[], int idimp, int npmax,
                    int nyzpm1, int idds) {
   ppdsortp32yzl_(parta,partb,npic,&npp,noff,nyzp,&idimp,&npmax,&nyzpm1,
                  &idds);
   return;
}

/*--------------------------------------------------------------------*/
void cppcguard32xl(float fxyz[], int nyzp[], int nx, int ndim, int nxe,
                   int nypmx, int nzpmx, int idds) {
   ppcguard32xl_(fxyz,nyzp,&nx,&ndim,&nxe,&nypmx,&nzpmx,&idds);
   return;
}

/*--------------------------------------------------------------------*/
void cppaguard32xl(float q[], int nyzp[], int nx, int nxe, int nypmx,
                   int nzpmx, int idds) {
   ppaguard32xl_(q,nyzp,&nx,&nxe,&nypmx,&nzpmx,&idds);
   return;
}

/*--------------------------------------------------------------------*/
void cppacguard32xl(float cu[], int nyzp[], int nx, int ndim, int nxe,
                    int nypmx, int nzpmx, int idds) {
   ppacguard32xl_(cu,nyzp,&nx,&ndim,&nxe,&nypmx,&nzpmx,&idds);
   return;
}

/*--------------------------------------------------------------------*/
void cppois332(float complex q[], float complex fxyz[], int isign,
               float complex ffc[], float ax, float ay, float az,
               float affp, float *we, int nx, int ny, int nz, int kstrt,
               int nvpy, int nvpz, int nzv, int kxyp, int kyzp,
               int nzhd) {
   ppois332_(q,fxyz,&isign,ffc,&ax,&ay,&az,&affp,we,&nx,&ny,&nz,&kstrt,
             &nvpy,&nvpz,&nzv,&kxyp,&kyzp,&nzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppcuperp32(float complex cu[], int nx, int ny, int nz, int kstrt,
                 int nvpy, int nvpz, int nzv, int kxyp, int kyzp) {
   ppcuperp32_(cu,&nx,&ny,&nz,&kstrt,&nvpy,&nvpz,&nzv,&kxyp,&kyzp);
   return;
}

/*--------------------------------------------------------------------*/
void cippbpoisp332(float complex cu[], float complex bxyz[],
                   float complex ffc[], float ci, float *wm, int nx,
                   int ny, int nz, int kstrt, int nvpy, int nvpz,
                   int nzv, int kxyp, int kyzp, int nzhd) {
   ippbpoisp332_(cu,bxyz,ffc,&ci,wm,&nx,&ny,&nz,&kstrt,&nvpy,&nvpz,&nzv,
                 &kxyp,&kyzp,&nzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppmaxwel32(float complex exyz[], float complex bxyz[],
                 float complex cu[], float complex ffc[], float affp,
                 float ci, float dt, float *wf, float *wm, int nx,
                 int ny, int nz, int kstrt, int nvpy, int nvpz, int nzv,
                 int kxyp, int kyzp, int nzhd) {
   ppmaxwel32_(exyz,bxyz,cu,ffc,&affp,&ci,&dt,wf,wm,&nx,&ny,&nz,&kstrt,
               &nvpy,&nvpz,&nzv,&kxyp,&kyzp,&nzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppemfield32(float complex fxyz[], float complex exyz[],
                  float complex ffc[], int isign, int nx, int ny,
                  int nz, int kstrt, int nvpy, int nvpz, int nzv,
                  int kxyp, int kyzp, int nzhd) {
   ppemfield32_(fxyz,exyz,ffc,&isign,&nx,&ny,&nz,&kstrt,&nvpy,&nvpz,
                &nzv,&kxyp,&kyzp,&nzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cwpfft32rinit(int mixup[], float complex sct[], int indx, int indy,
                   int indz, int nxhyzd, int nxyzhd) {
   wpfft32rinit_(mixup,sct,&indx,&indy,&indz,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppfft32rxx(float complex f[], int isign, int mixup[],
                 float complex sct[], int indx, int indy, int indz,
                 int kstrt, int nvp, int kypi, int kypp, int nxvh,
                 int kzpp, int kypd, int kzpd, int nxhyzd, int nxyzhd) {
   ppfft32rxx_(f,&isign,mixup,sct,&indx,&indy,&indz,&kstrt,&nvp,&kypi,
               &kypp,&nxvh,&kzpp,&kypd,&kzpd,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppfft32rxy(float complex g[], int isign, int mixup[],
                 float complex sct[], int indx, int indy, int indz,
                 int kstrt, int nvpy, int nvpz, int kxypi, int kxypp,
                 int nyv, int kzpp, int kxypd, int kzpd, int nxhyzd,
                 int nxyzhd) {
   ppfft32rxy_(g,&isign,mixup,sct,&indx,&indy,&indz,&kstrt,&nvpy,&nvpz,
               &kxypi,&kxypp,&nyv,&kzpp,&kxypd,&kzpd,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppfft32rxz(float complex h[], int isign, int mixup[],
                 float complex sct[], int indx, int indy, int indz,
                 int kstrt, int nvpy, int nvpz, int kxypi, int kxypp,
                 int nzv, int kyzp, int kxypd, int kyzpd, int nxhyzd,
                 int nxyzhd) {
   ppfft32rxz_(h,&isign,mixup,sct,&indx,&indy,&indz,&kstrt,&nvpy,&nvpz,
               &kxypi,&kxypp,&nzv,&kyzp,&kxypd,&kyzpd,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppfft32r3xx(float complex f[], int isign, int mixup[],
                  float complex sct[], int indx, int indy, int indz,
                  int kstrt, int nvp, int kypi, int kypp, int nxvh,
                  int kzpp, int kypd, int kzpd, int nxhyzd, int nxyzhd) {
   ppfft32r3xx_(f,&isign,mixup,sct,&indx,&indy,&indz,&kstrt,&nvp,&kypi,
                &kypp,&nxvh,&kzpp,&kypd,&kzpd,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppfft32r3xy(float complex g[], int isign, int mixup[],
                  float complex sct[], int indx, int indy, int indz,
                  int kstrt, int nvpy, int nvpz, int kxypi, int kxypp,
                  int nyv, int kzpp, int kxypd, int kzpd, int nxhyzd,
                  int nxyzhd) {
   ppfft32r3xy_(g,&isign,mixup,sct,&indx,&indy,&indz,&kstrt,&nvpy,&nvpz,
                &kxypi,&kxypp,&nyv,&kzpp,&kxypd,&kzpd,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cppfft32r3xz(float complex h[], int isign, int mixup[],
                  float complex sct[], int indx, int indy, int indz,
                  int kstrt, int nvpy, int nvpz, int kxypi, int kxypp,
                  int nzv, int kyzp, int kxypd, int kyzpd, int nxhyzd,
                  int nxyzhd) {
   ppfft32r3xz_(h,&isign,mixup,sct,&indx,&indy,&indz,&kstrt,&nvpy,&nvpz,
                &kxypi,&kxypp,&nzv,&kyzp,&kxypd,&kyzpd,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cwppfft32r(float complex f[], float complex g[], float complex h[],
                float complex bs[], float complex br[], int isign,
                int ntpose, int mixup[], float complex sct[],
                float *ttp, int indx, int indy, int indz, int kstrt,
                int nvpy, int nvpz, int nxvh, int nyv, int nzv,
                int kxyp, int kyp, int kyzp, int kzp, int kxypd,
                int kypd, int kyzpd, int kzpd, int kzyp, int nxhyzd,
                int nxyzhd) {
   wppfft32r_(f,g,h,bs,br,&isign,&ntpose,mixup,sct,ttp,&indx,&indy,
              &indz,&kstrt,&nvpy,&nvpz,&nxvh,&nyv,&nzv,&kxyp,&kyp,&kyzp,
              &kzp,&kxypd,&kypd,&kyzpd,&kzpd,&kzyp,&nxhyzd,&nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cwppfft32r3(float complex f[], float complex g[],
                 float complex h[], float complex bs[],
                 float complex br[], int isign, int ntpose, int mixup[],
                 float complex sct[], float *ttp, int indx, int indy,
                 int indz, int kstrt, int nvpy, int nvpz, int nxvh,
                 int nyv, int nzv, int kxyp, int kyp, int kyzp, int kzp,
                 int kxypd, int kypd, int kyzpd, int kzpd, int kzyp,
                 int nxhyzd, int nxyzhd) {
   wppfft32r3_(f,g,h,bs,br,&isign,&ntpose,mixup,sct,ttp,&indx,&indy,
               &indz,&kstrt,&nvpy,&nvpz,&nxvh,&nyv,&nzv,&kxyp,&kyp,
               &kyzp,&kzp,&kxypd,&kypd,&kyzpd,&kzpd,&kzyp,&nxhyzd,
               &nxyzhd);
   return;
}

