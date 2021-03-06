/* C Library for Skeleton 3D Electrostatic PIC Code */
/* written by Viktor K. Decyk, UCLA */

#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "push3.h"

/*--------------------------------------------------------------------*/
double ranorm() {
/* this program calculates a random number y from a gaussian distribution
   with zero mean and unit variance, according to the method of
   mueller and box:
      y(k) = (-2*ln(x(k)))**1/2*sin(2*pi*x(k+1))
      y(k+1) = (-2*ln(x(k)))**1/2*cos(2*pi*x(k+1)),
   where x is a random number uniformly distributed on (0,1).
   written for the ibm by viktor k. decyk, ucla
local data                                                              */
   static int r1 = 885098780, r2 = 1824280461;
   static int r4 = 1396483093, r5 = 55318673;
   static int iflg = 0;
   static double h1l = 65531.0, h1u = 32767.0, h2l = 65525.0;
   static double r0 = 0.0;
   int isc, i1;
   double ranorm, r3, asc, bsc, temp;
   if (iflg==1) {
      ranorm = r0;
      r0 = 0.0;
      iflg = 0;
      return ranorm;
   }
   isc = 65536;
   asc = (double) isc;
   bsc = asc*asc;
   i1 = r1 - (r1/isc)*isc;
   r3 = h1l*(double) r1 + asc*h1u*(double) i1;
   i1 = r3/bsc;
   r3 -= ((double) i1)*bsc;
   bsc = 0.5*bsc;
   i1 = r2/isc;
   isc = r2 - i1*isc;
   r0 = h1l*(double) r2 + asc*h1u*(double) isc;
   asc = 1.0/bsc;
   isc = r0*asc;
   r2 = r0 - ((double) isc)*bsc;
   r3 += (double) isc + 2.0*h1u*(double) i1;
   isc = r3*asc;
   r1 = r3 - ((double) isc)*bsc;
   temp = sqrt(-2.0*log((((double) r1) + ((double) r2)*asc)*asc));
   isc = 65536;
   asc = (double) isc;
   bsc = asc*asc;
   i1 = r4 - (r4/isc)*isc;
   r3 = h2l*(double) r4 + asc*h1u*(double) i1;
   i1 = r3/bsc;
   r3 -= ((double) i1)*bsc;
   bsc = 0.5*bsc;
   i1 = r5/isc;
   isc = r5 - i1*isc;
   r0 = h2l*(double) r5 + asc*h1u*(double) isc;
   asc = 1.0/bsc;
   isc = r0*asc;
   r5 = r0 - ((double) isc)*bsc;
   r3 += (double) isc + 2.0*h1u*(double) i1;
   isc = r3*asc;
   r4 = r3 - ((double) isc)*bsc;
   r0 = 6.28318530717959*((((double) r4) + ((double) r5)*asc)*asc);
   ranorm = temp*sin(r0);
   r0 = temp*cos(r0);
   iflg = 1;
   return ranorm;
}

/*--------------------------------------------------------------------*/
double randum() {
/* this is a version of the random number generator dprandom due to
   c. bingham and the yale computer center, producing numbers
   in the interval (0,1).  written for the sun by viktor k. decyk, ucla
local data                                                              */
   static int r1 = 1271199957, r2 = 1013501921;
   static double h1l = 65533.0, h1u = 32767.0;
   int isc, i1;
   double randum, r0, r3, asc, bsc;
   isc = 65536;
   asc = (double) isc;
   bsc = asc*asc;
   i1 = r1 - (r1/isc)*isc;
   r3 = h1l*(double) r1 + asc*h1u*(double) i1;
   i1 = r3/bsc;
   r3 = r3 - ((double) i1)*bsc;
   bsc = 0.5*bsc;
   i1 = r2/isc;
   isc = r2 - i1*isc;
   r0 = h1l*(double) r2 + asc*h1u*(double) isc;
   asc = 1.0/bsc;
   isc = r0*asc;
   r2 = r0 - ((double) isc)*bsc;
   r3 = r3 + ((double) isc + 2.0*h1u*(double) i1);
   isc = r3*asc;
   r1 = r3 - ((double) isc)*bsc;
   randum = ((double) r1 + ((double) r2)*asc)*asc;
   return randum;
}

/*--------------------------------------------------------------------*/
void cdistr3(float part[], float vtx, float vty, float vtz, float vdx,
             float vdy, float vdz, int npx, int npy, int npz, int idimp,
             int nop, int nx, int ny, int nz, int ipbc) {
/* for 3d code, this subroutine calculates initial particle co-ordinates
   and velocities with uniform density and maxwellian velocity with drift
   part[n][0] = position x of particle n
   part[n][1] = position y of particle n
   part[n][2] = position z of particle n
   part[n][3] = velocity vx of particle n
   part[n][4] = velocity vy of particle n
   part[n][5] = velocity vz of particle n
   vtx/vty/vtz = thermal velocity of electrons in x/y/z direction
   vdx/vdy/vdz = drift velocity of beam electrons in x/y/z direction
   npx/npy/npz = initial number of particles distributed in x/y/z
   direction
   idimp = size of phase space = 6
   nop = number of particles
   nx/ny/nz = system length in x/y/z direction
   ipbc = particle boundary condition = (0,1,2,3) =
   (none,3d periodic,3d reflecting,mixed 2d reflecting/1d periodic)
   ranorm = gaussian random number with zero mean and unit variance
local data                                                            */
   int j, k, l, k1, l1, npxy, npxyz;
   float edgelx, edgely, edgelz, at1, at2, at3, at4, at5;
   float sum1, sum2, sum3;
   double dsum1, dsum2, dsum3;
   npxy = npx*npy;
   npxyz = npxy*npz;
/* set boundary values */
   edgelx = 0.0;
   edgely = 0.0;
   edgelz = 0.0;
   at1 = (float) nx/(float) npx;
   at2 = (float) ny/(float) npy;
   at3 = (float) nz/(float) npz;
   if (ipbc==2) {
      edgelx = 1.0;
      edgely = 1.0;
      edgelz = 1.0;
      at1 = (float) (nx-2)/(float) npx;
      at2 = (float) (ny-2)/(float) npy;
      at3 = (float) (nz-2)/(float) npz;
   }
   else if (ipbc==3) {
      edgelx = 1.0;
      edgely = 1.0;
      edgelz = 0.0;
      at1 = (float) (nx-2)/(float) npx;
      at2 = (float) (ny-2)/(float) npy;
   }
/* uniform density profile */
   for (l = 0; l < npz; l++) {
      l1 = idimp*npxy*l;
      at5 = edgelz + at3*(((float) l) + 0.5);
      for (k = 0; k < npy; k++) {
         k1 = idimp*npx*k + l1;
         at4 = edgely + at2*(((float) k) + 0.5);
         for (j = 0; j < npx; j++) {
            part[idimp*j+k1] = edgelx + at1*(((float) j) + 0.5);
            part[1+idimp*j+k1] = at4;
            part[2+idimp*j+k1] = at5;
         }
      }
   }
/* maxwellian velocity distribution */
   for (j = 0; j < npxyz; j++) {
      part[3+idimp*j] = vtx*ranorm();
      part[4+idimp*j] = vty*ranorm();
      part[5+idimp*j] = vtz*ranorm();
   }
/* add correct drift */
   dsum1 = 0.0;
   dsum2 = 0.0;
   dsum3 = 0.0;
   for (j = 0; j < npxyz; j++) {
      dsum1 += part[3+idimp*j];
      dsum2 += part[4+idimp*j];
      dsum3 += part[5+idimp*j];
   }
   sum1 = dsum1;
   sum2 = dsum2;
   sum3 = dsum3;
   at1 = 1.0/(float) npxyz;
   sum1 = at1*sum1 - vdx;
   sum2 = at1*sum2 - vdy;
   sum3 = at1*sum3 - vdz;
   for (j = 0; j < npxyz; j++) {
      part[3+idimp*j] -= sum1;
      part[4+idimp*j] -= sum2;
      part[5+idimp*j] -= sum3;
   }
   return;
}

/*--------------------------------------------------------------------*/
void cgpush3l(float part[], float fxyz[], float qbm, float dt,
              float *ek, int idimp, int nop, int nx, int ny, int nz,
              int nxv, int nyv, int nzv, int ipbc) {
/* for 3d code, this subroutine updates particle co-ordinates and
   velocities using leap-frog scheme in time and first-order linear
   interpolation in space
   scalar version using guard cells
   94 flops/particle, 30 loads, 6 stores
   input: all, output: part, ek
   equations used are:
   vx(t+dt/2) = vx(t-dt/2) + (q/m)*fx(x(t),y(t),z(t))*dt,
   vy(t+dt/2) = vy(t-dt/2) + (q/m)*fy(x(t),y(t),z(t))*dt,
   vz(t+dt/2) = vz(t-dt/2) + (q/m)*fz(x(t),y(t),z(t))*dt,
   where q/m is charge/mass, and
   x(t+dt) = x(t) + vx(t+dt/2)*dt, y(t+dt) = y(t) + vy(t+dt/2)*dt,
   z(t+dt) = z(t) + vz(t+dt/2)*dt
   fx(x(t),y(t),z(t)), fy(x(t),y(t),z(t)), and fz(x(t),y(t),z(t))
   are approximated by interpolation from the nearest grid points:
   fx(x,y,z) = (1-dz)*((1-dy)*((1-dx)*fx(n,m,l)+dx*fx(n+1,m,l))
                  + dy*((1-dx)*fx(n,m+1,l) + dx*fx(n+1,m+1,l)))
             + dz*((1-dy)*((1-dx)*fx(n,m,l+1)+dx*fx(n+1,m,l+1))
                  + dy*((1-dx)*fx(n,m+1,l+1) + dx*fx(n+1,m+1,l+1)))
   fy(x,y,z) = (1-dz)*((1-dy)*((1-dx)*fy(n,m,l)+dx*fy(n+1,m,l))
                  + dy*((1-dx)*fy(n,m+1,l) + dx*fy(n+1,m+1,l)))
             + dz*((1-dy)*((1-dx)*fy(n,m,l+1)+dx*fy(n+1,m,l+1))
                  + dy*((1-dx)*fy(n,m+1,l+1) + dx*fy(n+1,m+1,l+1)))
   fz(x,y,z) = (1-dz)*((1-dy)*((1-dx)*fz(n,m,l)+dx*fz(n+1,m,l))
                  + dy*((1-dx)*fz(n,m+1,l) + dx*fz(n+1,m+1,l)))
             + dz*((1-dy)*((1-dx)*fz(n,m,l+1)+dx*fz(n+1,m,l+1))
                  + dy*((1-dx)*fz(n,m+1,l+1) + dx*fz(n+1,m+1,l+1)))
   where n,m,l = leftmost grid points and dx = x-n, dy = y-m, dz = z-l
   part[n][0] = position x of particle n
   part[n][1] = position y of particle n
   part[n][2] = position z of particle n
   part[n][3] = velocity vx of particle n
   part[n][4] = velocity vy of particle n
   part[n][5] = velocity vz of particle n
   fxyz[l][k][j][0] = x component of force/charge at grid (j,k,l)
   fxyz[l][k][j][1] = y component of force/charge at grid (j,k,l)
   fxyz[l][k][j][2] = z component of force/charge at grid (j,k,l)
   that is, convolution of electric field over particle shape
   qbm = particle charge/mass ratio
   dt = time interval between successive calculations
   kinetic energy/mass at time t is also calculated, using
   ek = .125*sum((vx(t+dt/2)+vx(t-dt/2))**2+(vy(t+dt/2)+vy(t-dt/2))**2+
   (vz(t+dt/2)+vz(t-dt/2))**2)
   idimp = size of phase space = 6
   nop = number of particles
   nx/ny/nz = system length in x/y/z direction
   nxv = second dimension of field array, must be >= nx+1
   nyv = third dimension of field array, must be >= ny+1
   nzv = fourth dimension of field array, must be >= nz+1
   ipbc = particle boundary condition = (0,1,2,3) =
   (none,3d periodic,3d reflecting,mixed 2d reflecting/1d periodic)
local data                                                            */
   int j, nn, mm, ll, np, mp, lp, nxv3, nxyv3;
   float qtm, edgelx, edgely, edgelz, edgerx, edgery, edgerz;
   float dxp, dyp, dzp, amx, amy, amz, dx1, dx, dy, dz, vx, vy, vz;
   double sum1;
   nxv3 = 3*nxv;
   nxyv3 = nxv3*nyv;
   qtm = qbm*dt;
   sum1 = 0.0;
/* set boundary values */
   edgelx = 0.0;
   edgely = 0.0;
   edgelz = 0.0;
   edgerx = (float) nx;
   edgery = (float) ny;
   edgerz = (float) nz;
   if (ipbc==2) {
      edgelx = 1.0;
      edgely = 1.0;
      edgelz = 1.0;
      edgerx = (float) (nx-1);
      edgery = (float) (ny-1);
      edgerz = (float) (nz-1);
   }
   else if (ipbc==3) {
      edgelx = 1.0;
      edgely = 1.0;
      edgerx = (float) (nx-1);
      edgery = (float) (ny-1);
   }
   for (j = 0; j < nop; j++) {
/* find interpolation weights */
      nn = part[idimp*j];
      mm = part[1+idimp*j];
      ll = part[2+idimp*j];
      dxp = part[idimp*j] - (float) nn;
      dyp = part[1+idimp*j] - (float) mm;
      dzp = part[2+idimp*j] - (float) ll;
      nn = 3*nn;
      mm = nxv3*mm;
      ll = nxyv3*ll;
      amx = 1.0 - dxp;
      amy = 1.0 - dyp;
      lp = ll + nxyv3;
      dx1 = dxp*dyp;
      dyp = amx*dyp;
      amx = amx*amy;
      mp = mm + nxv3;
      amz = 1.0 - dzp;
      np = nn + 3;
      amy = dxp*amy;
/* find acceleration */
      dx = amz*(amx*fxyz[nn+mm+ll] + amy*fxyz[np+mm+ll]
              + dyp*fxyz[nn+mp+ll] + dx1*fxyz[np+mp+ll])
         + dzp*(amx*fxyz[nn+mm+lp] + amy*fxyz[np+mm+lp]
              + dyp*fxyz[nn+mp+lp] + dx1*fxyz[np+mp+lp]);
      dy = amz*(amx*fxyz[1+nn+mm+ll] + amy*fxyz[1+np+mm+ll]
              + dyp*fxyz[1+nn+mp+ll] + dx1*fxyz[1+np+mp+ll])
         + dzp*(amx*fxyz[1+nn+mm+lp] + amy*fxyz[1+np+mm+lp]
              + dyp*fxyz[1+nn+mp+lp] + dx1*fxyz[1+np+mp+lp]);
      dz = amz*(amx*fxyz[2+nn+mm+ll] + amy*fxyz[2+np+mm+ll]
              + dyp*fxyz[2+nn+mp+ll] + dx1*fxyz[2+np+mp+ll])
         + dzp*(amx*fxyz[2+nn+mm+lp] + amy*fxyz[2+np+mm+lp]
              + dyp*fxyz[2+nn+mp+lp] + dx1*fxyz[2+np+mp+lp]);
/* new velocity */
      vx = part[3+idimp*j];
      vy = part[4+idimp*j];
      vz = part[5+idimp*j];
      dx = vx + qtm*dx;
      dy = vy + qtm*dy;
      dz = vz + qtm*dz;
/* average kinetic energy */
      vx += dx;
      vy += dy;
      vz += dz;
      sum1 += vx*vx + vy*vy + vz*vz;
      part[3+idimp*j] = dx;
      part[4+idimp*j] = dy;
      part[5+idimp*j] = dz;
/* new position */
      dx = part[idimp*j] + dx*dt;
      dy = part[1+idimp*j] + dy*dt;
      dz = part[2+idimp*j] + dz*dt;
/* periodic boundary conditions */
      if (ipbc==1) {
         if (dx < edgelx) dx += edgerx;
         if (dx >= edgerx) dx -= edgerx;
         if (dy < edgely) dy += edgery;
         if (dy >= edgery) dy -= edgery;
         if (dz < edgelz) dz += edgerz;
         if (dz >= edgerz) dz -= edgerz;
      }
/* reflecting boundary conditions */
      else if (ipbc==2) {
         if ((dx < edgelx) || (dx >= edgerx)) {
            dx = part[idimp*j];
            part[3+idimp*j] = -part[3+idimp*j];
         }
         if ((dy < edgely) || (dy >= edgery)) {
            dy = part[1+idimp*j];
            part[4+idimp*j] = -part[4+idimp*j];
         }
         if ((dz < edgelz) || (dz >= edgerz)) {
            dz = part[2+idimp*j];
            part[5+idimp*j] = -part[5+idimp*j];
         }
      }
/* mixed reflecting/periodic boundary conditions */
      else if (ipbc==3) {
         if ((dx < edgelx) || (dx >= edgerx)) {
            dx = part[idimp*j];
            part[3+idimp*j] = -part[3+idimp*j];
         }
         if ((dy < edgely) || (dy >= edgery)) {
            dy = part[1+idimp*j];
            part[4+idimp*j] = -part[4+idimp*j];
         }
         if (dz < edgelz) dz += edgerz;
         if (dz >= edgerz) dz -= edgerz;
      }
/* set new position */
      part[idimp*j] = dx;
      part[1+idimp*j] = dy;
      part[2+idimp*j] = dz;
   }
/* normalize kinetic energy */
   *ek += 0.125*sum1;
   return;
}

/*--------------------------------------------------------------------*/
void cgpost3l(float part[], float q[], float qm, int nop, int idimp,
              int nxv, int nyv, int nzv) {
/* for 3d code, this subroutine calculates particle charge density
   using first-order linear interpolation, periodic boundaries
   scalar version using guard cells
   33 flops/particle, 11 loads, 8 stores
   input: all, output: q
   charge density is approximated by values at the nearest grid points
   q(n,m,l)=qm*(1.-dx)*(1.-dy)*(1.-dz)
   q(n+1,m,l)=qm*dx*(1.-dy)*(1.-dz)
   q(n,m+1,l)=qm*(1.-dx)*dy*(1.-dz)
   q(n+1,m+1,l)=qm*dx*dy*(1.-dz)
   q(n,m,l+1)=qm*(1.-dx)*(1.-dy)*dz
   q(n+1,m,l+1)=qm*dx*(1.-dy)*dz
   q(n,m+1,l+1)=qm*(1.-dx)*dy*dz
   q(n+1,m+1,l+1)=qm*dx*dy*dz
   where n,m,l = leftmost grid points and dx = x-n, dy = y-m, dz = z-l
   part[n][0] = position x of particle n
   part[n][1] = position y of particle n
   part[n][2] = position z of particle n
   q[l][k][j] = charge density at grid point j,k,l
   qm = charge on particle, in units of e
   nop = number of particles
   idimp = size of phase space = 6
   nxv = first dimension of charge array, must be >= nx+1
   nyv = second dimension of charge array, must be >= ny+1
   nzv = third dimension of charge array, must be >= nz+1
local data                                                            */
   int j, nn, mm, ll, np, mp, lp, nxyv;
   float dx1, dxp, dyp, dzp, amx, amy, amz;
   nxyv = nxv*nyv;
   for (j = 0; j < nop; j++) {
/* find interpolation weights */
      nn = part[idimp*j];
      mm = part[1+idimp*j];
      ll = part[2+idimp*j];
      dxp = qm*(part[idimp*j] - (float) nn);
      dyp = part[1+idimp*j] - (float) mm;
      dzp = part[2+idimp*j] - (float) ll;
      mm = nxv*mm;
      ll = nxyv*ll;
      amx = qm - dxp;
      amy = 1.0 - dyp;
      lp = ll + nxyv;
      dx1 = dxp*dyp;
      dyp = amx*dyp;
      amx = amx*amy;
      mp = mm + nxv;
      amz = 1.0 - dzp;
      np = nn + 1;
      amy = dxp*amy;
/* deposit charge */
      q[nn+mm+ll] += amx*amz;
      q[np+mm+ll] += amy*amz;
      q[nn+mp+ll] += dyp*amz;
      q[np+mp+ll] += dx1*amz;
      q[nn+mm+lp] += amx*dzp;
      q[np+mm+lp] += amy*dzp;
      q[nn+mp+lp] += dyp*dzp;
      q[np+mp+lp] += dx1*dzp;
   }
   return;
}

/*--------------------------------------------------------------------*/
void cdsortp3yzl(float parta[], float partb[], int npic[], int idimp,
                 int nop, int ny1, int nyz1) {
/* this subroutine sorts particles by y,z grid
   linear interpolation
   part = particle array
   part[n][1] = position y of particle n
   part[n][2] = position z of particle n
   npic = address offset for reordering particles
   idimp = size of phase space = 6
   nop = number of particles
   ny1 = system length in y direction + 1
   nyz1 = ny1*nz1, where nz1 = system length in z direction + 1
local data                                                            */
   int i, j, k, m, l, isum, ist, ip;
/* clear counter array */
   for (k = 0; k < nyz1; k++) {
      npic[k] = 0;
   }
/* find how many particles in each grid */
   for (j = 0; j < nop; j++) {
      m = parta[1+idimp*j];
      l = parta[2+idimp*j];
      l = m + ny1*l;
      npic[l] += 1;
   }
/* find address offset */
   isum = 0;
   for (k = 0; k < nyz1; k++) {
      ist = npic[k];
      npic[k] = isum;
      isum += ist;
   }
/* find addresses of particles at each grid and reorder particles */
   for (j = 0; j < nop; j++) {
      m = parta[1+idimp*j];
      l = parta[2+idimp*j];
      l = m + ny1*l;
      ip = npic[l];
      for (i = 0; i < idimp; i++) {
         partb[i+idimp*ip] = parta[i+idimp*j];
      }
      npic[l] = ip + 1;
   }
   return;
}

/*--------------------------------------------------------------------*/
void ccguard3l(float fxyz[], int nx, int ny, int nz, int nxe, int nye,
               int nze) {
/* replicate extended periodic vector field fxyz
   linear interpolation
   nx/ny/nz = system length in x/y direction
   nxe = first dimension of field arrays, must be >= nx+1
   nye = second dimension of field arrays, must be >= ny+1
   nze = third dimension of field arrays, must be >= nz+1
local data                                                 */
   int j, k, l, nxye3, ll;
   nxye3 = 3*nxe*nye;
/* copy edges of extended field */
   for (l = 0; l < nz; l++) {
      ll = nxye3*l;
      for (k = 0; k < ny; k++) {
         fxyz[3*nx+3*nxe*k+ll] = fxyz[3*nxe*k+ll];
         fxyz[1+3*nx+3*nxe*k+ll] = fxyz[1+3*nxe*k+ll];
         fxyz[2+3*nx+3*nxe*k+ll] = fxyz[2+3*nxe*k+ll];
      }
      for (j = 0; j < nx; j++) {
         fxyz[3*j+3*nxe*ny+ll] = fxyz[3*j+ll];
         fxyz[1+3*j+3*nxe*ny+ll] = fxyz[1+3*j+ll];
         fxyz[2+3*j+3*nxe*ny+ll] = fxyz[2+3*j+ll];
      }
      fxyz[3*nx+3*nxe*ny+ll] = fxyz[ll];
      fxyz[1+3*nx+3*nxe*ny+ll] = fxyz[1+ll];
      fxyz[2+3*nx+3*nxe*ny+ll] = fxyz[2+ll];

   }
   for (k = 0; k < ny; k++) {
      for (j = 0; j < nx; j++) {
         fxyz[3*j+3*nxe*k+nxye3*nz] = fxyz[3*j+3*nxe*k];
         fxyz[1+3*j+3*nxe*k+nxye3*nz] = fxyz[1+3*j+3*nxe*k];
         fxyz[2+3*j+3*nxe*k+nxye3*nz] = fxyz[2+3*j+3*nxe*k];
      }
      fxyz[3*nx+3*nxe*k+nxye3*nz] = fxyz[3*nxe*k];
      fxyz[1+3*nx+3*nxe*k+nxye3*nz] = fxyz[1+3*nxe*k];
      fxyz[2+3*nx+3*nxe*k+nxye3*nz] = fxyz[2+3*nxe*k];
   }
   for (j = 0; j < nx; j++) {
      fxyz[3*j+3*nxe*ny+nxye3*nz] = fxyz[3*j];
      fxyz[1+3*j+3*nxe*ny+nxye3*nz] = fxyz[1+3*j];
      fxyz[2+3*j+3*nxe*ny+nxye3*nz] = fxyz[2+3*j];
   }
   fxyz[3*nx+3*nxe*ny+nxye3*nz] = fxyz[0];
   fxyz[1+3*nx+3*nxe*ny+nxye3*nz] = fxyz[1];
   fxyz[2+3*nx+3*nxe*ny+nxye3*nz] = fxyz[2];
   return;
}

/*--------------------------------------------------------------------*/
void caguard3l(float q[], int nx, int ny, int nz, int nxe, int nye,
               int nze) {
/* accumulate extended periodic scalar field q
   linear interpolation
   nx/ny/nz = system length in x/y direction
   nxe = first dimension of field arrays, must be >= nx+1
   nye = second dimension of field arrays, must be >= ny+1
   nze = third dimension of field arrays, must be >= nz+1
local data                                                 */
   int j, k, l, nxye, ll;
   nxye = nxe*nye;
/* accumulate edges of extended field */
   for (l = 0; l < nz; l++) {
      ll = nxye*l;
      for (k = 0; k < ny; k++) {
         q[nxe*k+ll] += q[nx+nxe*k+ll];
         q[nx+nxe*k+ll] = 0.0;
      }
      for (j = 0; j < nx; j++) {
         q[j+ll] += q[j+nxe*ny+ll];
         q[j+nxe*ny+ll] = 0.0;
      }
      q[ll] += q[nx+nxe*ny+ll];
      q[nx+nxe*ny+ll] = 0.0;
   }
   for (k = 0; k < ny; k++) {
      for (j = 0; j < nx; j++) {
         q[j+nxe*k] += q[j+nxe*k+nxye*nz];
         q[j+nxe*k+nxye*nz] = 0.0;
      }
      q[nxe*k] += q[nx+nxe*k+nxye*nz];
      q[nx+nxe*k+nxye*nz] = 0.0;

   }
   for (j = 0; j < nx; j++) {
      q[j] += q[j+nxe*ny+nxye*nz];
      q[j+nxe*ny+nxye*nz] = 0.0;
   }
   q[0] += q[nx+nxe*ny+nxye*nz];
   q[nx+nxe*ny+nxye*nz] = 0.0;
   return;
}

/*--------------------------------------------------------------------*/
void cpois33(float complex q[], float complex fxyz[], int isign,
             float complex ffc[], float ax, float ay, float az,
             float affp, float *we, int nx, int ny, int nz, int nxvh,
             int nyv, int nzv, int nxhd, int nyhd, int nzhd) {
/* this subroutine solves 3d poisson's equation in fourier space for
   force/charge (or convolution of electric field over particle shape)
   with periodic boundary conditions.
   for isign = 0, output: ffc
   input: isign,ax,ay,az,affp,nx,ny,nz,nxvh,nyv,nzv,nxhd,nyhd,nzhd
   for isign = -1, output: fxyz, we
   input: q,ffc,isign,nx,ny,nz,nxvh,nyv,nzv,nxhd,nyhd,nzhd
   approximate flop count is:
   59*nxc*nyc*nzc + 26*(nxc*nyc + nxc*nzc + nyc*nzc)
   where nxc = nx/2 - 1, nyc = ny/2 - 1, nzc = nz/2 - 1
   if isign = 0, form factor array is prepared
   if isign is not equal to 0, force/charge is calculated
   equation used is:
   fx[kz][ky][kx] = -sqrt(-1)*kx*g[kz][ky][kx]*s[kz][ky][kx],
   fy[kz][ky][kx] = -sqrt(-1)*ky*g[kz][ky][kx]*s[kz][ky][kx],
   fz[kz][ky][kx] = -sqrt(-1)*kz*g[kz][ky][kx]*s[kz][ky][kx],
   where kx = 2pi*j/nx, ky = 2pi*k/ny, kz = 2pi*l/nz, and
   j,k,l = fourier mode numbers,
   g[kz][ky][kx] = (affp/(kx**2+ky**2+kz**2))*s[kz][ky][kx],
   s[kz][ky][kx] = exp(-((kx*ax)**2+(ky*ay)**2+(kz*az)**2)/2), except for
   fx(kx=pi) = fy(kx=pi) = fz(kx=pi) = 0,
   fx(ky=pi) = fy(ky=pi) = fx(ky=pi) = 0,
   fx(kz=pi) = fy(kz=pi) = fz(kz=pi) = 0,
   fx(kx=0,ky=0,kz=0) = fy(kx=0,ky=0,kz=0) = fz(kx=0,ky=0,kz=0) = 0.
   q[l][k][j] = complex charge density for fourier mode (j,k,l)
   fxyz[l][k][j][0] = x component of complex force/charge
   fxyz[l][k][j][1] = y component of complex force/charge
   fxyz[l][k][j][2] = z component of complex force/charge
   all for fourier mode (j,k,l)
   cimag(ffc[l][k][j]) = finite-size particle shape factor s
   for fourier mode (j,k,l)
   creal(ffc[l][k][j]) = potential green's function g
   for fourier mode (j,k,l)
   ax/ay/az = half-width of particle in x/y/z direction
   affp = normalization constant = nx*ny*nz/np,
   where np=number of particles
   electric field energy is also calculated, using
   we = nx*ny*nz*sum((affp/(kx**2+ky**2+kz**2))*
      |q[kz][ky][kx]*s[kz][ky][kx]|**2)
   nx/ny/nz = system length in x/y/z direction
   nxvh = first dimension of field arrays, must be >= nxh
   nyv = second dimension of field arrays, must be >= ny
   nzv = third dimension of field arrays, must be >= nz
   nxhd = first dimension of form factor array, must be >= nxh
   nyhd = second dimension of form factor array, must be >= nyh
   nzhd = third dimension of form factor array, must be >= nzh
local data                                                 */
   int nxh, nyh, nzh, j, k, l, k1, l1, kk, kj, ll, lj, nxyhd, nxvyh; 
   float dnx, dny, dnz, dkx, dky, dkz, at1, at2, at3, at4, at5, at6;
   float complex zero, zt1, zt2;
   double wp;
   nxh = nx/2;
   nyh = 1 > ny/2 ? 1 : ny/2;
   nzh = 1 > nz/2 ? 1 : nz/2;
   nxyhd = nxhd*nyhd;
   nxvyh = nxvh*nyv;
   dnx = 6.28318530717959/(float) nx;
   dny = 6.28318530717959/(float) ny;
   dnz = 6.28318530717959/(float) nz;
   zero = 0.0 + 0.0*_Complex_I;
   if (isign != 0)
      goto L40;
/* prepare form factor array */
   for (l = 0; l < nzh; l++) {
      dkz = dnz*(float) l;
      ll = nxyhd*l;
      at1 = dkz*dkz;
      at2 = pow((dkz*az),2);
      for (k = 0; k < nyh; k++) {
         dky = dny*(float) k;
         kk = nxhd*k;
         at3 = dky*dky + at1;
         at4 = pow((dky*ay),2) + at2;
         for (j = 0; j < nxh; j++) {
            dkx = dnx*(float) j;
            at5 = dkx*dkx + at3;
            at6 = exp(-0.5*(pow((dkx*ax),2) + at4));
            if (at5==0.0) {
               ffc[j+kk+ll] = affp + 1.0*_Complex_I;
            }
            else {
               ffc[j+kk+ll] = (affp*at6/at5) + at6*_Complex_I;
            }
         }
      }
   }
   return;
/* calculate force/charge and sum field energy */
L40: wp = 0.0;
/* mode numbers 0 < kx < nx/2, 0 < ky < ny/2, and 0 < kz < nz/2 */
   for (l = 1; l < nzh; l++) {
      dkz = dnz*(float) l;
      ll = nxyhd*l;
      lj = nxvyh*l;
      l1 = nxvyh*nz - lj;
      for (k = 1; k < nyh; k++) {
         dky = dny*(float) k;
         kk = nxhd*k;
         kj = nxvh*k;
         k1 = nxvh*ny - kj;
         for (j = 1; j < nxh; j++) {
            at1 = crealf(ffc[j+kk+ll])*cimagf(ffc[j+kk+ll]);
            at2 = at1*dnx*(float) j;
            at3 = dky*at1;
            at4 = dkz*at1;
            zt1 = cimagf(q[j+kj+lj]) - crealf(q[j+kj+lj])*_Complex_I;
            zt2 = cimagf(q[j+k1+lj]) - crealf(q[j+k1+lj])*_Complex_I;
            fxyz[3*(j+kj+lj)] = at2*zt1;
            fxyz[1+3*(j+kj+lj)] = at3*zt1;
            fxyz[2+3*(j+kj+lj)] = at4*zt1;
            fxyz[3*(j+k1+lj)] = at2*zt2;
            fxyz[1+3*(j+k1+lj)] = -at3*zt2;
            fxyz[2+3*(j+k1+lj)] = at4*zt2;
            zt1 = cimagf(q[j+kj+l1]) - crealf(q[j+kj+l1])*_Complex_I;
            zt2 = cimagf(q[j+k1+l1]) - crealf(q[j+k1+l1])*_Complex_I;
            fxyz[3*(j+kj+l1)] = at2*zt1;
            fxyz[1+3*(j+kj+l1)] = at3*zt1;
            fxyz[2+3*(j+kj+l1)] = -at4*zt1;
            fxyz[3*(j+k1+l1)] = at2*zt2;
            fxyz[1+3*(j+k1+l1)] = -at3*zt2;
            fxyz[2+3*(j+k1+l1)] = -at4*zt2;
            wp += at1*(q[j+kj+lj]*conjf(q[j+kj+lj])                 
               + q[j+k1+lj]*conjf(q[j+k1+lj])
               + q[j+kj+l1]*conjf(q[j+kj+l1])      
               + q[j+k1+l1]*conjf(q[j+k1+l1]));
         }
      }
/* mode numbers kx = 0, nx/2 */
      for (k = 1; k < nyh; k++) {
         kk = nxhd*k;
         kj = nxvh*k;
         k1 = nxvh*ny - kj;
         at1 = crealf(ffc[kk+ll])*cimagf(ffc[kk+ll]);
         at3 = at1*dny*(float) k;
         at4 = dkz*at1;
         zt1 = cimagf(q[kj+lj]) - crealf(q[kj+lj])*_Complex_I;
         zt2 = cimagf(q[kj+l1]) - crealf(q[kj+l1])*_Complex_I;
         fxyz[3*(kj+lj)] = zero;
         fxyz[1+3*(kj+lj)] = at3*zt1;
         fxyz[2+3*(kj+lj)] = at4*zt1;
         fxyz[3*(k1+lj)] = zero;
         fxyz[1+3*(k1+lj)] = zero;
         fxyz[2+3*(k1+lj)] = zero;
         fxyz[3*(kj+l1)] = zero;
         fxyz[1+3*(kj+l1)] = at3*zt2;
         fxyz[2+3*(kj+l1)] = -at4*zt2;
         fxyz[3*(k1+l1)] = zero;
         fxyz[1+3*(k1+l1)] = zero;
         fxyz[2+3*(k1+l1)] = zero;
         wp += at1*(q[kj+lj]*conjf(q[kj+lj])
            + q[kj+l1]*conjf(q[kj+l1]));
      }
/* mode numbers ky = 0, ny/2 */
      k1 = nxvh*nyh;
      for (j = 1; j < nxh; j++) {
         at1 = crealf(ffc[j+ll])*cimagf(ffc[j+ll]);
         at2 = at1*dnx*(float) j;  
         at4 = dkz*at1;
         zt1 = cimagf(q[j+lj]) - crealf(q[j+lj])*_Complex_I;
         zt2 = cimagf(q[j+l1]) - crealf(q[j+l1])*_Complex_I;
         fxyz[3*(j+lj)] = at2*zt1;
         fxyz[1+3*(j+lj)] = zero;
         fxyz[2+3*(j+lj)] = at4*zt1;
         fxyz[3*(j+k1+lj)] = zero;
         fxyz[1+3*(j+k1+lj)] = zero;
         fxyz[2+3*(j+k1+lj)] = zero;
         fxyz[3*(j+l1)] = at2*zt2;
         fxyz[1+3*(j+l1)] = zero;
         fxyz[2+3*(j+l1)] = -at4*zt2;
         fxyz[3*(j+k1+l1)] = zero;
         fxyz[1+3*(j+k1+l1)] = zero;
         fxyz[2+3*(j+k1+l1)] = zero;
         wp += at1*(q[j+lj]*conjf(q[j+lj])                           
            + q[j+l1]*conjf(q[j+l1]));
      }
/* mode numbers kx = 0, nx/2 */
      at1 = crealf(ffc[ll])*cimagf(ffc[ll]);
      at4 = dkz*at1;
      zt1 = cimagf(q[lj]) - crealf(q[lj])*_Complex_I;
      fxyz[3*lj] = zero;
      fxyz[1+3*lj] = zero;
      fxyz[2+3*lj] = at4*zt1;
      fxyz[3*(k1+lj)] = zero;
      fxyz[1+3*(k1+lj)] = zero;
      fxyz[2+3*(k1+lj)] = zero;
      fxyz[3*l1] = zero;
      fxyz[1+3*l1] = zero;
      fxyz[2+3*l1] = zero;
      fxyz[3*(k1+l1)] = zero;
      fxyz[1+3*(k1+l1)] = zero;
      fxyz[2+3*(k1+l1)] = zero;
      wp += at1*(q[lj]*conjf(q[lj]));
   }
/* mode numbers kz = 0, nz/2 */
   l1 = nxvyh*nzh;
   for (k = 1; k < nyh; k++) {
      dky = dny*(float) k;
      kk = nxhd*k;
      kj = nxvh*k;
      k1 = nxvh*ny - kj;
      for (j = 1; j < nxh; j++) {
         at1 = crealf(ffc[j+kk])*cimagf(ffc[j+kk]);
         at2 = at1*dnx*(float) j;
         at3 = dky*at1;
         zt1 = cimagf(q[j+kj]) - crealf(q[j+kj])*_Complex_I;
         zt2 = cimagf(q[j+k1]) - crealf(q[j+k1])*_Complex_I;
         fxyz[3*(j+kj)] = at2*zt1;
         fxyz[1+3*(j+kj)] = at3*zt1;
         fxyz[2+3*(j+kj)] = zero;
         fxyz[3*(j+k1)] = at2*zt2;
         fxyz[1+3*(j+k1)] = -at3*zt2;
         fxyz[2+3*(j+k1)] = zero;
         fxyz[3*(j+kj+l1)] = zero;
         fxyz[1+3*(j+kj+l1)] = zero;
         fxyz[2+3*(j+kj+l1)] = zero;
         fxyz[3*(j+k1+l1)] = zero;
         fxyz[1+3*(j+k1+l1)] = zero;
         fxyz[2+3*(j+k1+l1)] = zero;
         wp += at1*(q[j+kj]*conjf(q[j+kj]) + q[j+k1]*conjf(q[j+k1]));
      }
   }
/* mode numbers kx = 0, nx/2 */
   for (k = 1; k < nyh; k++) {
      kk = nxhd*k;
      kj = nxvh*k;
      k1 = nxvh*ny - kj;
      at1 = crealf(ffc[kk])*cimagf(ffc[kk]);
      at3 = at1*dny*(float) k;
      zt1 = cimagf(q[kj]) - crealf(q[kj])*_Complex_I;
      fxyz[3*kj] = zero;
      fxyz[1+3*kj] = at3*zt1;
      fxyz[2+3*kj] = zero;
      fxyz[3*k1] = zero;
      fxyz[1+3*k1] = zero;
      fxyz[2+3*k1] = zero;
      fxyz[3*(kj+l1)] = zero;
      fxyz[1+3*(kj+l1)] = zero;
      fxyz[2+3*(kj+l1)] = zero;
      fxyz[3*(k1+l1)] = zero;
      fxyz[1+3*(k1+l1)] = zero;
      fxyz[2+3*(k1+l1)] = zero;
      wp += at1*(q[kj]*conjf(q[kj]));
   }
/* mode numbers ky = 0, ny/2 */
   k1 = nxvh*nyh;
   for (j = 1; j < nxh; j++) {
      at1 = crealf(ffc[j])*cimagf(ffc[j]);
      at2 = at1*dnx*(float) j;
      zt1 = cimagf(q[j]) - crealf(q[j])*_Complex_I;
      fxyz[3*j] = at2*zt1;
      fxyz[1+3*j] = zero;
      fxyz[2+3*j] = zero;
      fxyz[3*(j+k1)] = zero;
      fxyz[1+3*(j+k1)] = zero;
      fxyz[2+3*(j+k1)] = zero;
      fxyz[3*(j+l1)] = zero;
      fxyz[1+3*(j+l1)] = zero;
      fxyz[2+3*(j+l1)] = zero;
      fxyz[3*(j+k1+l1)] = zero;
      fxyz[1+3*(j+k1+l1)] = zero;
      fxyz[2+3*(j+k1+l1)] = zero;
      wp += at1*(q[j]*conjf(q[j]));
   }
   fxyz[0] = zero;
   fxyz[1] = zero;
   fxyz[2] = zero;
   fxyz[3*k1] = zero;
   fxyz[1+3*k1] = zero;
   fxyz[2+3*k1] = zero;
   fxyz[3*l1] = zero;
   fxyz[1+3*l1] = zero;
   fxyz[2+3*l1] = zero;
   fxyz[3*(k1+l1)] = zero;
   fxyz[1+3*(k1+l1)] = zero;
   fxyz[2+3*(k1+l1)] = zero;
   *we = wp*((float) nx)*((float) ny)*((float) nz);
   return;
}

/*--------------------------------------------------------------------*/
void cwfft3rinit(int mixup[], float complex sct[], int indx, int indy,
                 int indz, int nxhyzd, int nxyzhd) {
/* this subroutine calculates tables needed by a three dimensional
   real to complex fast fourier transform and its inverse.
   input: indx, indy, indz, nxhyzd, nxyzhd
   output: mixup, sct
   mixup = array of bit reversed addresses
   sct = sine/cosine table
   indx/indy/indz = exponent which determines length in x/y/z direction,
   where nx=2**indx, ny=2**indy, nz=2**indz
   nxhyzd = maximum of (nx/2,ny,nz)
   nxyzhd = one half of maximum of (nx,ny,nz)
   written by viktor k. decyk, ucla
local data                                                            */
   int indx1, ndx1yz, nx, ny, nz, nxyz, nxhyz, nxyzh;
   int j, k, lb, ll, jb, it;
   float dnxyz, arg;
   indx1 = indx - 1;
   ndx1yz = indx1 > indy ? indx1 : indy;
   ndx1yz = ndx1yz > indz ? ndx1yz : indz;
   nx = 1L<<indx;
   ny = 1L<<indy;
   nz = 1L<<indz;
   nxyz = nx > ny ? nx : ny;
   nxyz = nxyz > nz ? nxyz : nz;
   nxhyz = 1L<<ndx1yz;
/* bit-reverse index table: mixup[j] = 1 + reversed bits of j */
   for (j = 0; j < nxhyz; j++) {
      lb = j;
      ll = 0;
      for (k = 0; k < ndx1yz; k++) {
         jb = lb/2;
         it = lb - 2*jb;
         lb = jb;
         ll = 2*ll + it;
      }
      mixup[j] = ll + 1;
   }
/* sine/cosine table for the angles 2*n*pi/nxyz */
   nxyzh = nxyz/2;
   dnxyz = 6.28318530717959/(float) nxyz;
   for (j = 0; j < nxyzh; j++) {
      arg = dnxyz*(float) j;
      sct[j] = cosf(arg) - sinf(arg)*_Complex_I;
   }
   return;
}

/*--------------------------------------------------------------------*/
void cfft3rxy(float complex f[], int isign, int mixup[],
              float complex sct[], int indx, int indy, int indz,
              int nzi, int nzp, int nxhd, int nyd, int nzd, int nxhyzd,
              int nxyzhd) {
/* this subroutine performs the x-y part of a three dimensional real to
   complex fast fourier transform and its inverse, for a subset of z,
   using complex arithmetic
   for isign = (-1,1), input: all, output: f
   for isign = -1, approximate flop count: N*(5*log2(N) + 19/2)
   for isign = 1,  approximate flop count: N*(5*log2(N) + 15/2)
   where N = (nx/2)*ny*nz
   indx/indy/indz = exponent which determines length in x/y/z direction,
   where nx=2**indx, ny=2**indy, nz=2**indz
   if isign = -1, an inverse fourier transform is performed
   f[i][m][n] = (1/nx*ny*nz)*sum(f[i][k][j]*exp(-sqrt(-1)*2pi*n*j/nx)*
         exp(-sqrt(-1)*2pi*m*k/ny))
   if isign = 1, a forward fourier transform is performed
   f[l][k][j] = sum(f[l][m][n]*exp(sqrt(-1)*2pi*n*j/nx)*
         exp(sqrt(-1)*2pi*m*k/ny))
   mixup = array of bit reversed addresses
   sct = sine/cosine table
   nzi = initial z index used
   nzp = number of z indices used
   nxhd = first dimension of f
   nyd,nzd = second and third dimensions of f
   nxhyzd = maximum of (nx/2,ny,nz)
   nxyzhd = maximum of (nx,ny,nz)/2
   fourier coefficients are stored as follows:
   f[l][k][j] = real, imaginary part of mode j,k,l
   where 0 <= j < nx/2, 0 <= k < ny, 0 <= l < nz, except for
   f[l][k][0] = real, imaginary part of mode nx/2,k,l,
   where ny/2+1 <= k < ny and 0 <= l < nz, and
   f[l][0][0] = real, imaginary part of mode nx/2,0,l,
   f[l][ny/2][0] = real, imaginary part mode nx/2,ny/2,l,
   where nz/2+1 <= l < nz, and
   imag(f[0][0][0]) = real part of mode nx/2,0,0
   imag(f[0][ny/2][0]) = real part of mode nx/2,ny/2,0
   imag(f[nz/2][0][0]) = real part of mode nx/2,0,nz/2
   imag(f[nz/2][ny/2][0]) = real part of mode nx/2,ny/2,nz/2
   using jpl storage convention, as described in:
   E. Huang, P. C. Liewer, V. K. Decyk, and R. D. Ferraro, "Concurrent
   Three-Dimensional Fast Fourier Transform Algorithms for Coarse-Grained
   Distributed Memory Parallel Computers," Caltech CRPC Report 217-50,
   December 1993.
   written by viktor k. decyk, ucla
local data                                                            */
   int indx1, ndx1yz, nx, nxh, nxhh, ny, nyh;
   int nz, nxyz, nxhyz, nzt, nrx, nry, nxhyd;
   int i, j, k, l, n, nn, j1, j2, k1, k2, ns, ns2, km, kmr, joff;
   float ani;
   float complex t1, t2, t3;
   if (isign==0)
      return;
   indx1 = indx - 1;
   ndx1yz = indx1 > indy ? indx1 : indy;
   ndx1yz = ndx1yz > indz ? ndx1yz : indz;
   nx = 1L<<indx;
   nxh = nx/2;
   nxhh = nx/4;
   ny = 1L<<indy;
   nyh = ny/2;
   nz = 1L<<indz;
   nxyz = nx > ny ? nx : ny;
   nxyz = nxyz > nz ? nxyz : nz;
   nxhyz = 1L<<ndx1yz;
   nzt = nzi + nzp - 1;
   nxhyd = nxhd*nyd;
   if (isign > 0)
      goto L180;
/* inverse fourier transform */
   for (n = nzi-1; n < nzt; n++) {
      nn = nxhyd*n;
/* bit-reverse array elements in x */
      nrx = nxhyz/nxh;
      for (j = 0; j < nxh; j++) {
         j1 = (mixup[j] - 1)/nrx;
         if (j >= j1)
            continue;
         for (i = 0; i < ny; i++) {
            joff = nxhd*i + nn;
            t1 = f[j1+joff];
            f[j1+joff] = f[j+joff];
            f[j+joff] = t1;
         }
      }
/* first transform in x */
      nrx = nxyz/nxh;
      ns = 1;
      for (l = 0; l < indx1; l++) {
         ns2 = ns + ns;
         km = nxhh/ns;
         kmr = km*nrx;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = j + k1;
               j2 = j + k2;
               t1 = sct[kmr*j];
               for (i = 0; i < ny; i++) {
                  joff = nxhd*i + nn;
                  t2 = t1*f[j2+joff];
                  f[j2+joff] = f[j1+joff] - t2;
                  f[j1+joff] += t2;
               }
            }
         }
         ns = ns2;
      }
/* unscramble coefficients and normalize */
      kmr = nxyz/nx;
      ani = 0.5/(((float) nx)*((float) ny)*((float) nz));
      for (j = 1; j < nxhh; j++) {
         t3 = cimagf(sct[kmr*j]) - crealf(sct[kmr*j])*_Complex_I;
         for (k = 0; k < ny; k++) {
            joff = nxhd*k + nn;
            t2 = conjf(f[nxh-j+joff]);
            t1 = f[j+joff] + t2;
            t2 = (f[j+joff] - t2)*t3;
            f[j+joff] = ani*(t1 + t2);
            f[nxh-j+joff] = ani*conjf(t1 - t2);
         }
      }
      ani = 2.0*ani;
      for (k = 0; k < ny; k++) {
         joff = nxhd*k + nn;
         f[nxhh+joff] = ani*conjf(f[nxhh+joff]);
         f[joff] = ani*((crealf(f[joff]) + cimagf(f[joff]))
                   + (crealf(f[joff]) - cimagf(f[joff]))*_Complex_I);
      }
/* bit-reverse array elements in y */
      nry = nxhyz/ny;
      for (k = 0; k < ny; k++) {
         joff = nxhd*k + nn;
         k1 = (mixup[k] - 1)/nry;
         if (k >= k1)
            continue;
         k1 = nxhd*k1 + nn;
         for (i = 0; i < nxh; i++) {
            t1 = f[i+k1];
            f[i+k1] = f[i+joff];
            f[i+joff] = t1;
         }
      }
/* then transform in y */
      nry = nxyz/ny;
      ns = 1;
      for (l = 0; l < indy; l++) {
         ns2 = ns + ns;
         km = nyh/ns;
         kmr = km*nry;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = nxhd*(j + k1) + nn;
               j2 = nxhd*(j + k2) + nn;
               t1 = sct[kmr*j];
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[i+j2];
                  f[i+j2] = f[i+j1] - t2;
                  f[i+j1] += t2;
               }
            }
         }
         ns = ns2;
      }
/* unscramble modes kx = 0, nx/2 */
      for (k = 1; k < nyh; k++) {
         joff = nxhd*k;
         k1 = nxhd*ny - joff + nn;
         joff += nn;
         t1 = f[k1];
         f[k1] = 0.5*(cimagf(f[joff] + t1)
                  + crealf(f[joff] - t1)*_Complex_I);
         f[joff] = 0.5*(crealf(f[joff] + t1)
                    + cimagf(f[joff] - t1)*_Complex_I);
      }
   }
   return;
/* forward fourier transform */
L180: for (n = nzi-1; n < nzt; n++) {
      nn = nxhyd*n;
/* scramble modes kx = 0, nx/2 */
      for (k = 1; k < nyh; k++) {
         joff = nxhd*k;
         k1 = nxhd*ny - joff + nn;
         joff += nn;
         t1 = cimagf(f[k1]) + crealf(f[k1])*_Complex_I;
         f[k1] = conjf(f[joff] - t1);
         f[joff] += t1;
      }
/* bit-reverse array elements in y */
      nry = nxhyz/ny;
      for (k = 0; k < ny; k++) {
         joff = nxhd*k + nn;
         k1 = (mixup[k] - 1)/nry;
         if (k >= k1)
            continue;
         k1 = nxhd*k1 + nn;
         for (i = 0; i < nxh; i++) {
            t1 = f[i+k1];
            f[i+k1] = f[i+joff];
            f[i+joff] = t1;
         }
      }
/* then transform in y */
      nry = nxyz/ny;
      ns = 1;
      for (l = 0; l < indy; l++) {
         ns2 = ns + ns;
         km = nyh/ns;
         kmr = km*nry;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = nxhd*(j + k1) + nn;
               j2 = nxhd*(j + k2) + nn;
               t1 = conjf(sct[kmr*j]);
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[i+j2];
                  f[i+j2] = f[i+j1] - t2;
                  f[i+j1] += t2;
               }
            }
         }
         ns = ns2;
      }
/* scramble coefficients */
      kmr = nxyz/nx;
      for (j = 1; j < nxhh; j++) {
         t3 = cimagf(sct[kmr*j]) + crealf(sct[kmr*j])*_Complex_I;
         for (k = 0; k < ny; k++) {
            joff = nxhd*k + nn;
            t2 = conjf(f[nxh-j+joff]);
            t1 = f[j+joff] + t2;
            t2 = (f[j+joff] - t2)*t3;
            f[j+joff] = t1 + t2;
            f[nxh-j+joff] = conjf(t1 - t2);
         }
      }
      for (k = 0; k < ny; k++) {
         joff = nxhd*k + nn;
         f[nxhh+joff] = 2.0*conjf(f[nxhh+joff]);
         f[joff] = (crealf(f[joff]) + cimagf(f[joff]))
                   + (crealf(f[joff]) - cimagf(f[joff]))*_Complex_I;
      }
/* bit-reverse array elements in x */
      nrx = nxhyz/nxh;
      for (j = 0; j < nxh; j++) {
         j1 = (mixup[j] - 1)/nrx;
         if (j >= j1)
            continue;
         for (i = 0; i < ny; i++) {
            joff = nxhd*i + nn;
            t1 = f[j1+joff];
            f[j1+joff] = f[j+joff];
            f[j+joff] = t1;
         }
      }
/* finally transform in x */
      nrx = nxyz/nxh;
      ns = 1;
      for (l = 0; l < indx1; l++) {
         ns2 = ns + ns;
         km = nxhh/ns;
         kmr = km*nrx;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = j + k1;
               j2 = j + k2;
               t1 = conjf(sct[kmr*j]);
               for (i = 0; i < ny; i++) {
                  joff = nxhd*i + nn;
                  t2 = t1*f[j2+joff];
                  f[j2+joff] = f[j1+joff] - t2;
                  f[j1+joff] += t2;
               }
            }
         }
         ns = ns2;
      }
   }
   return;
}

/*--------------------------------------------------------------------*/
void cfft3rxz(float complex f[], int isign, int mixup[],
              float complex sct[], int indx, int indy, int indz,
              int nyi, int nyp, int nxhd, int nyd, int nzd, int nxhyzd,
              int nxyzhd) {
/* this subroutine performs the z part of a three dimensional real to
   complex fast fourier transform and its inverse, for a subset of y,
   using complex arithmetic
   for isign = (-1,1), input: all, output: f
   for isign = -1, approximate flop count: N*(5*log2(N) + 19/2)
   for isign = 1,  approximate flop count: N*(5*log2(N) + 15/2)
   where N = (nx/2)*ny*nz
   indx/indy/indz = exponent which determines length in x/y/z direction,
   where nx=2**indx, ny=2**indy, nz=2**indz
   if isign = -1, an inverse fourier transform is performed
   f[l][k][j] = sum(f[i][k][j]*exp(-sqrt(-1)*2pi*l*i/nz))
   if isign = 1, a forward fourier transform is performed
   f[i][m][n] = sum(f[l][m][n]*exp(sqrt(-1)*2pi*l*i/nz))
   mixup = array of bit reversed addresses
   sct = sine/cosine table
   nyi = initial y index used
   nyp = number of y indices used
   nxhd = first dimension of f
   nyd,nzd = second and third dimensions of f
   nxhyzd = maximum of (nx/2,ny,nz)
   nxyzhd = maximum of (nx,ny,nz)/2
   fourier coefficients are stored as follows:
   f[l][k][j] = real, imaginary part of mode j,k,l
   where 0 <= j < nx/2, 0 <= k < ny, 0 <= l < nz, except for
   f[l][k][0] = real, imaginary part of mode nx/2,k,l,
   where ny/2+1 <= k < ny and 0 <= l < nz, and
   f[l][0][0] = real, imaginary part of mode nx/2,0,l,
   f[l][ny/2][0] = real, imaginary part mode nx/2,ny/2,l,
   where nz/2+1 <= l < nz, and
   imag(f[0][0][0]) = real part of mode nx/2,0,0
   imag(f[0][ny/2][0]) = real part of mode nx/2,ny/2,0
   imag(f[nz/2][0][0]) = real part of mode nx/2,0,nz/2
   imag(f[nz/2][ny/2][0]) = real part of mode nx/2,ny/2,nz/2
   using jpl storage convention, as described in:
   E. Huang, P. C. Liewer, V. K. Decyk, and R. D. Ferraro, "Concurrent
   Three-Dimensional Fast Fourier Transform Algorithms for Coarse-Grained
   Distributed Memory Parallel Computers," Caltech CRPC Report 217-50,
   December 1993.
   written by viktor k. decyk, ucla
local data                                                            */
   int indx1, ndx1yz, nx, nxh, ny, nyh;
   int nz, nzh, nxyz, nxhyz, nyt, nrz, nxhyd;
   int i, j, k, l, n, ll, j1, j2, k1, k2, l1, ns, ns2, km, kmr, i0, i1;
   float complex t1, t2;
   if (isign==0)
      return;
   indx1 = indx - 1;
   ndx1yz = indx1 > indy ? indx1 : indy;
   ndx1yz = ndx1yz > indz ? ndx1yz : indz;
   nx = 1L<<indx;
   nxh = nx/2;
   ny = 1L<<indy;
   nyh = ny/2;
   nz = 1L<<indz;
   nzh = nz/2;
   nxyz = nx > ny ? nx : ny;
   nxyz = nxyz > nz ? nxyz : nz;
   nxhyz = 1L<<ndx1yz;
   nyt = nyi + nyp - 1;
   nxhyd = nxhd*nyd;
   if (isign > 0)
      goto L100;
/* inverse fourier transform */
/* bit-reverse array elements in z */
   nrz = nxhyz/nz;
   for (l = 0; l < nz; l++) {
      ll = nxhyd*l;
      l1 = (mixup[l] - 1)/nrz;
      if (l >= l1)
         continue;
      l1 = nxhyd*l1;
      for (n = nyi-1; n < nyt; n++) {
         i1 = nxhd*n;
         i0 = i1 + ll;
         i1 += l1;
         for (i = 0; i < nxh; i++) {
            t1 = f[i+i1];
            f[i+i1] = f[i+i0];
            f[i+i0] = t1;
         }
      }
   }
/* finally transform in z */
   nrz = nxyz/nz;
   ns = 1;
   for (l = 0; l < indz; l++) {
      ns2 = ns + ns;
      km = nzh/ns;
      kmr = km*nrz;
      for (k = 0; k < km; k++) {
         k1 = ns2*k;
         k2 = k1 + ns;
         for (j = 0; j < ns; j++) {
            j1 = nxhyd*(j + k1);
            j2 = nxhyd*(j + k2);
            t1 = sct[kmr*j];
            for (n = nyi-1; n < nyt; n++) {
               i1 = nxhd*n;
               i0 = i1 + j1;
               i1 += j2;
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[i+i1];
                  f[i+i1] = f[i+i0] - t2;
                  f[i+i0] += t2;
               }
            }
         }
      }
      ns = ns2;
   }
/* unscramble modes kx = 0, nx/2 */
   for (n = 1; n < nzh; n++) {
      ll = nxhyd*n;
      l1 = nxhyd*nz - ll;
      if (nyi==1) {
         t1 = f[l1];
         f[l1] = 0.5*(cimagf(f[ll] + t1)
                    + crealf(f[ll] - t1)*_Complex_I);
         f[ll] = 0.5*(crealf(f[ll] + t1)
                    + cimagf(f[ll] - t1)*_Complex_I);
      }
      if ((nyi <= (nyh+1)) && (nyt >= (nyh+1))) {
         i1 = nxhd*nyh;
         i0 = i1 + ll;
         i1 += l1;
         t1 = f[i1];
         f[i1] = 0.5*(cimagf(f[i0] + t1)
                  +   crealf(f[i0] - t1)*_Complex_I);
         f[i0] = 0.5*(crealf(f[i0] + t1)
                    + cimagf(f[i0] - t1)*_Complex_I);
      }
   }
   return;
/* forward fourier transform */
/* scramble modes kx = 0, nx/2 */
L100: for (n = 1; n < nzh; n++) {
      ll = nxhyd*n;
      l1 = nxhyd*nz - ll;
      if (nyi==1) {
         t1 = cimagf(f[l1]) + crealf(f[l1])*_Complex_I;
         f[l1] = conjf(f[ll] - t1);
         f[ll] += t1;
      }
      if ((nyi <= (nyh+1)) && (nyt >= (nyh+1))) {
         i1 = nxhd*nyh;
         i0 = i1 + ll;
         i1 += l1;
         t1 = cimagf(f[i1]) + crealf(f[i1])*_Complex_I;
         f[i1] = conjf(f[i0] - t1);
         f[i0] += t1;
      }
   }
/* bit-reverse array elements in z */
   nrz = nxhyz/nz;
   for (l = 0; l < nz; l++) {
      ll = nxhyd*l;
      l1 = (mixup[l] - 1)/nrz;
      if (l >= l1)
         continue;
      l1 = nxhyd*l1;
      for (n = nyi-1; n < nyt; n++) {
         i1 = nxhd*n;
         i0 = i1 + ll;
         i1 += l1;
         for (i = 0; i < nxh; i++) {
            t1 = f[i+i1];
            f[i+i1] = f[i+i0];
            f[i+i0] = t1;
         }
      }
   }
/* first transform in z */
   nrz = nxyz/nz;
   ns = 1;
   for (l = 0; l < indz; l++) {
      ns2 = ns + ns;
      km = nzh/ns;
      kmr = km*nrz;
      for (k = 0; k < km; k++) {
         k1 = ns2*k;
         k2 = k1 + ns;
         for (j = 0; j < ns; j++) {
            j1 = nxhyd*(j + k1);
            j2 = nxhyd*(j + k2);
            t1 = conjf(sct[kmr*j]);
            for (n = nyi-1; n < nyt; n++) {
               i1 = nxhd*n;
               i0 = i1 + j1;
               i1 += j2;
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[i+i1];
                  f[i+i1] = f[i+i0] - t2;
                  f[i+i0] += t2;
               }
            }
         }
      }
      ns = ns2;
   }
   return;
}

/*--------------------------------------------------------------------*/
void cfft3r3xy(float complex f[], int isign, int mixup[],
               float complex sct[], int indx, int indy, int indz,
               int nzi, int nzp, int nxhd, int nyd, int nzd, int nxhyzd,
               int nxyzhd) {
/* this subroutine performs the x-y part of 3 three dimensional complex
   to real fast fourier transforms and their inverses, for a subset of z,
   using complex arithmetic
   for isign = (-1,1), input: all, output: f
   for isign = -1, approximate flop count: N*(5*log2(N) + 19/2)
   for isign = 1,  approximate flop count: N*(5*log2(N) + 15/2)
   where N = (nx/2)*ny*nz
   indx/indy/indz = exponent which determines length in x/y/z direction,
   where nx=2**indx, ny=2**indy, nz=2**indz
   if isign = -1, three inverse fourier transforms is performed
   f[i][m][n][0:2] = (1/nx*ny*nz)*sum(f[i][k][j][0:2]*exp(-sqrt(-1)*2pi*n*j/nx)
         *exp(-sqrt(-1)*2pi*m*k/ny))
   if isign = 1, three forward fourier transforms are performed
   f[l][k][j][0:2] = sum(f[l][m][n][0:2]*exp(sqrt(-1)*2pi*n*j/nx)*
         exp(sqrt(-1)*2pi*m*k/ny))
   mixup = array of bit reversed addresses
   sct = sine/cosine table
   nzi = initial z index used
   nzp = number of z indices used
   nxhd = second dimension of f
   nyd,nzd = third and fourth dimensions of f
   nxhyzd = maximum of (nx/2,ny,nz)
   nxyzhd = maximum of (nx,ny,nz)/2
   fourier coefficients are stored as follows:
   f[l][k][j][0:2] = real, imaginary part of mode j,k,l
   where 0 <= j < nx/2, 0 <= k < ny, 0 <= l < nz, except for
   f[l][k][0][0:2] = real, imaginary part of mode nx/2,k,l,
   where ny/2+1 <= k < ny and 0 <= l < nz, and
   f[l][0][0][0:2] = real, imaginary part of mode nx/2,0,l,
   f[l][ny/2][0][0:2] = real, imaginary part mode nx/2,ny/2,l,
   where nz/2+1 <= l < nz, and
   imag(f[0][0][0][0:2]) = real part of mode nx/2,0,0
   imag(f[0][ny/2][0][0:2]) = real part of mode nx/2,ny/2,0
   imag(f[nz/2][0][0][0:2]) = real part of mode nx/2,0,nz/2
   imag(f[nz/2][ny/2][0][0:2]) = real part of mode nx/2,ny/2,nz/2
   using jpl storage convention, as described in:
   E. Huang, P. C. Liewer, V. K. Decyk, and R. D. Ferraro, "Concurrent
   Three-Dimensional Fast Fourier Transform Algorithms for Coarse-Grained
   Distributed Memory Parallel Computers," Caltech CRPC Report 217-50,
   December 1993.
   written by viktor k. decyk, ucla
local data                                                            */
   int indx1, ndx1yz, nx, nxh, nxhh, ny, nyh;
   int nz, nxyz, nxhyz, nzt, nrx, nry, nxhd3, nxhyd;
   int i, j, k, l, n, nn, jj, j1, j2, k1, k2, ns, ns2, km, kmr, joff;
   float at1, at2, ani;
   float complex t1, t2, t3, t4;
   if (isign==0)
      return;
   indx1 = indx - 1;
   ndx1yz = indx1 > indy ? indx1 : indy;
   ndx1yz = ndx1yz > indz ? ndx1yz : indz;
   nx = 1L<<indx;
   nxh = nx/2;
   nxhh = nx/4;
   ny = 1L<<indy;
   nyh = ny/2;
   nz = 1L<<indz;
   nxyz = nx > ny ? nx : ny;
   nxyz = nxyz > nz ? nxyz : nz;
   nxhyz = 1L<<ndx1yz;
   nzt = nzi + nzp - 1;
   nxhd3 = 3*nxhd;
   nxhyd = nxhd3*nyd;
   if (isign > 0)
      goto L230;
/* inverse fourier transform */
   for (n = nzi-1; n < nzt; n++) {
      nn = nxhyd*n;
/* swap complex components */
      for (i = 0; i < ny; i++) {
         joff = nxhd3*i + nn;
         for (j = 0; j < nxh; j++) {
            at1 = crealf(f[2+3*j+joff]);
            f[2+3*j+joff] = crealf(f[1+3*j+joff])
                            + cimagf(f[2+3*j+joff])*_Complex_I;
            at2 = cimagf(f[1+3*j+joff]);
            f[1+3*j+joff] = cimagf(f[3*j+joff]) + at1*_Complex_I;
            f[3*j+joff] = crealf(f[3*j+joff]) + at2*_Complex_I;
         }
      }
/* bit-reverse array elements in x */
      nrx = nxhyz/nxh;
      for (j = 0; j < nxh; j++) {
         j1 = (mixup[j] - 1)/nrx;
         if (j >= j1)
            continue;
         for (i = 0; i < ny; i++) {
            joff = nxhd3*i + nn;
            t1 = f[3*j1+joff];
            t2 = f[1+3*j1+joff];
            t3 = f[2+3*j1+joff];
            f[3*j1+joff] = f[3*j+joff];
            f[1+3*j1+joff] = f[1+3*j+joff];
            f[2+3*j1+joff] = f[2+3*j+joff];
            f[3*j+joff] = t1;
            f[1+3*j+joff] = t2;
            f[2+3*j+joff] = t3;
         }
      }
/* first transform in x */
      nrx = nxyz/nxh;
      ns = 1;
      for (l = 0; l < indx1; l++) {
         ns2 = ns + ns;
         km = nxhh/ns;
         kmr = km*nrx;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = j + k1;
               j2 = j + k2;
               t1 = sct[kmr*j];
               for (i = 0; i < ny; i++) {
                  joff = nxhd3*i + nn;
                  t2 = t1*f[3*j2+joff];
                  t3 = t1*f[1+3*j2+joff];
                  t4 = t1*f[2+3*j2+joff];
                  f[3*j2+joff] = f[3*j1+joff] - t2;
                  f[1+3*j2+joff] = f[1+3*j1+joff] - t3;
                  f[2+3*j2+joff] = f[2+3*j1+joff] - t4;
                  f[3*j1+joff] += t2;
                  f[1+3*j1+joff] += t3;
                  f[2+3*j1+joff] += t4;
               }
            }
         }
         ns = ns2;
      }
/* unscramble coefficients and normalize */
      kmr = nxyz/nx;
      ani = 0.5/(((float) nx)*((float) ny)*((float) nz));
      for (j = 1; j < nxhh; j++) {
         t3 = cimagf(sct[kmr*j]) - crealf(sct[kmr*j])*_Complex_I;
         for (k = 0; k < ny; k++) {
            joff = nxhd3*k + nn;
            for (jj = 0; jj < 3; jj++) {
               t2 = conjf(f[jj+3*(nxh-j)+joff]);
               t1 = f[jj+3*j+joff] + t2;
               t2 = (f[jj+3*j+joff] - t2)*t3;
               f[jj+3*j+joff] = ani*(t1 + t2);
               f[jj+3*(nxh-j)+joff] = ani*conjf(t1 - t2);
            }
         }
      }
      ani = 2.0*ani;
      for (k = 0; k < ny; k++) {
         joff = nxhd3*k + nn;
         for (jj = 0; jj < 3; jj++) {
            f[jj+3*nxhh+joff] = ani*conjf(f[jj+3*nxhh+joff]);
            f[jj+joff] = ani*((crealf(f[jj+joff]) 
                          + cimagf(f[jj+joff]))
                          + (crealf(f[jj+joff])
                          - cimagf(f[jj+joff]))*_Complex_I);
         }
      }
/* bit-reverse array elements in y */
      nry = nxhyz/ny;
      for (k = 0; k < ny; k++) {
         joff = nxhd3*k + nn;
         k1 = (mixup[k] - 1)/nry;
         if (k >= k1)
            continue;
         k1 = nxhd3*k1 + nn;
         for (i = 0; i < nxh; i++) {
            t1 = f[3*i+k1];
            t2 = f[1+3*i+k1];
            t3 = f[2+3*i+k1];
            f[3*i+k1] = f[3*i+joff];
            f[1+3*i+k1] = f[1+3*i+joff];
            f[2+3*i+k1] = f[2+3*i+joff];
            f[3*i+joff] = t1;
            f[1+3*i+joff] = t2;
            f[2+3*i+joff] = t3;
         }
      }
/* then transform in y */
      nry = nxyz/ny;
      ns = 1;
      for (l = 0; l < indy; l++) {
         ns2 = ns + ns;
         km = nyh/ns;
         kmr = km*nry;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = nxhd3*(j + k1) + nn;
               j2 = nxhd3*(j + k2) + nn;
               t1 = sct[kmr*j];
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[3*i+j2];
                  t3 = t1*f[1+3*i+j2];
                  t4 = t1*f[2+3*i+j2];
                  f[3*i+j2] = f[3*i+j1] - t2;
                  f[1+3*i+j2] = f[1+3*i+j1] - t3;
                  f[2+3*i+j2] = f[2+3*i+j1] - t4;
                  f[3*i+j1] += t2;
                  f[1+3*i+j1] += t3;
                  f[2+3*i+j1] += t4;
               }
            }
         }
         ns = ns2;
      }
/* unscramble modes kx = 0, nx/2 */
      for (k = 1; k < nyh; k++) {
         joff = nxhd3*k;
         k1 = nxhd3*ny - joff + nn;
         joff += nn;
         for (jj = 0; jj < 3; jj++) {
            t1 = f[jj+k1];
            f[jj+k1] = 0.5*(cimagf(f[jj+joff] + t1)
                        + crealf(f[jj+joff] - t1)*_Complex_I);
            f[jj+joff] = 0.5*(crealf(f[jj+joff] + t1)
                          + cimagf(f[jj+joff] - t1)*_Complex_I);
         }
      }
   }
   return;
/* forward fourier transform */
L230: for (n = nzi-1; n < nzt; n++) {
      nn = nxhyd*n;
/* scramble modes kx = 0, nx/2 */
      for (k = 1; k < nyh; k++) {
         joff = nxhd3*k;
         k1 = nxhd3*ny - joff + nn;
         joff += nn;
         for (jj = 0; jj < 3; jj++) {
            t1 = cimagf(f[jj+k1]) + crealf(f[jj+k1])*_Complex_I;
            f[jj+k1] = conjf(f[jj+joff] - t1);
            f[jj+joff] += t1;
         }
      }
/* bit-reverse array elements in y */
      nry = nxhyz/ny;
      for (k = 0; k < ny; k++) {
         joff = nxhd3*k + nn;
         k1 = (mixup[k] - 1)/nry;
         if (k >= k1)
            continue;
         k1 = nxhd3*k1 + nn;
         for (i = 0; i < nxh; i++) {
            t1 = f[3*i+k1];
            t2 = f[1+3*i+k1];
            t3 = f[2+3*i+k1];
            f[3*i+k1] = f[3*i+joff];
            f[1+3*i+k1] = f[1+3*i+joff];
            f[2+3*i+k1] = f[2+3*i+joff];
            f[3*i+joff] = t1;
            f[1+3*i+joff] = t2;
            f[2+3*i+joff] = t3;
         }
      }
/* then transform in y */
      nry = nxyz/ny;
      ns = 1;
      for (l = 0; l < indy; l++) {
         ns2 = ns + ns;
         km = nyh/ns;
         kmr = km*nry;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = nxhd3*(j + k1) + nn;
               j2 = nxhd3*(j + k2) + nn;
               t1 = conjf(sct[kmr*j]);
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[3*i+j2];
                  t3 = t1*f[1+3*i+j2];
                  t4 = t1*f[2+3*i+j2];
                  f[3*i+j2] = f[3*i+j1] - t2;
                  f[1+3*i+j2] = f[1+3*i+j1] - t3;
                  f[2+3*i+j2] = f[2+3*i+j1] - t4;
                  f[3*i+j1] += t2;
                  f[1+3*i+j1] += t3;
                  f[2+3*i+j1] += t4;
               }
            }
         }
         ns = ns2;
      }
/* scramble coefficients */
      kmr = nxyz/nx;
      for (j = 1; j < nxhh; j++) {
         t3 = cimagf(sct[kmr*j]) + crealf(sct[kmr*j])*_Complex_I;
         for (k = 0; k < ny; k++) {
            joff = nxhd3*k + nn;
            for (jj = 0; jj < 3; jj++) {
               t2 = conjf(f[jj+3*(nxh-j)+joff]);
               t1 = f[jj+3*j+joff] + t2;
               t2 = (f[jj+3*j+joff] - t2)*t3;
               f[jj+3*j+joff] = t1 + t2;
               f[jj+3*(nxh-j)+joff] = conjf(t1 - t2);
            }
         }
      }
      for (k = 0; k < ny; k++) {
         joff = nxhd3*k + nn;
         for (jj = 0; jj < 3; jj++) {
            f[jj+3*nxhh+joff] = 2.0*conjf(f[jj+3*nxhh+joff]);
            f[jj+joff] = (crealf(f[jj+joff]) + cimagf(f[jj+joff]))
                       + (crealf(f[jj+joff])
                       - cimagf(f[jj+joff]))*_Complex_I;
         }
      }
/* bit-reverse array elements in x */
      nrx = nxhyz/nxh;
      for (j = 0; j < nxh; j++) {
         j1 = (mixup[j] - 1)/nrx;
         if (j >= j1)
            continue;
         for (i = 0; i < ny; i++) {
            joff = nxhd3*i + nn;
            t1 = f[3*j1+joff];
            t2 = f[1+3*j1+joff];
            t3 = f[2+3*j1+joff];
            f[3*j1+joff] = f[3*j+joff];
            f[1+3*j1+joff] = f[1+3*j+joff];
            f[2+3*j1+joff] = f[2+3*j+joff];
            f[3*j+joff] = t1;
            f[1+3*j+joff] = t2;
            f[2+3*j+joff] = t3;
         }
      }
/* finally transform in x */
      nrx = nxyz/nxh;
      ns = 1;
      for (l = 0; l < indx1; l++) {
         ns2 = ns + ns;
         km = nxhh/ns;
         kmr = km*nrx;
         for (k = 0; k < km; k++) {
            k1 = ns2*k;
            k2 = k1 + ns;
            for (j = 0; j < ns; j++) {
               j1 = j + k1;
               j2 = j + k2;
               t1 = conjf(sct[kmr*j]);
               for (i = 0; i < ny; i++) {
                  joff = nxhd3*i + nn;
                  t2 = t1*f[3*j2+joff];
                  t3 = t1*f[1+3*j2+joff];
                  t4 = t1*f[2+3*j2+joff];
                  f[3*j2+joff] = f[3*j1+joff] - t2;
                  f[1+3*j2+joff] = f[1+3*j1+joff] - t3;
                  f[2+3*j2+joff] = f[2+3*j1+joff] - t4;
                  f[3*j1+joff] += t2;
                  f[1+3*j1+joff] += t3;
                  f[2+3*j1+joff] += t4;
               }
            }
         }
         ns = ns2;
      }
/* swap complex components */
      for (i = 0; i < ny; i++) {
         joff = nxhd3*i + nn;
         for (j = 0; j < nxh; j++) {
            at1 = crealf(f[2+3*j+joff]);
            f[2+3*j+joff] = cimagf(f[1+3*j+joff])
                            + cimagf(f[2+3*j+joff])*_Complex_I;
            at2 = crealf(f[1+3*j+joff]);
            f[1+3*j+joff] = at1 + cimagf(f[3*j+joff])*_Complex_I;
            f[3*j+joff] = crealf(f[3*j+joff]) + at2*_Complex_I;
         }
      }
   }
   return;
}

/*--------------------------------------------------------------------*/
void cfft3r3z(float complex f[], int isign, int mixup[],
              float complex sct[], int indx, int indy, int indz,
              int nyi, int nyp, int nxhd, int nyd, int nzd, int nxhyzd, 
              int nxyzhd) {
/* this subroutine performs the z part of 3 three dimensional complex to
   real fast fourier transforms and their inverses, for a subset of y,
   using complex arithmetic
   for isign = (-1,1), input: all, output: f
   for isign = -1, approximate flop count: N*(5*log2(N) + 19/2)
   for isign = 1,  approximate flop count: N*(5*log2(N) + 15/2)
   where N = (nx/2)*ny*nz
   indx/indy/indz = exponent which determines length in x/y/z direction,
   where nx=2**indx, ny=2**indy, nz=2**indz
   if isign = -1, three inverse fourier transforms is performed
   f[l][k][j][0:2] = sum(f[i][k][j][0:2]*exp(-sqrt(-1)*2pi*l*i/nz))
   if isign = 1, three forward fourier transforms are performed
   f[i][m][n][0:2] = sum(f[l][m][n][0:2]*exp(sqrt(-1)*2pi*l*i/nz))
   mixup = array of bit reversed addresses
   sct = sine/cosine table
   nyi = initial y index used
   nyp = number of y indices used
   nxhd = second dimension of f
   nyd,nzd = third and fourth dimensions of f
   nxhyzd = maximum of (nx/2,ny,nz)
   nxyzhd = maximum of (nx,ny,nz)/2
   fourier coefficients are stored as follows:
   f[l][k][j][0:2] = real, imaginary part of mode j,k,l
   where 0 <= j < nx/2, 0 <= k < ny, 0 <= l < nz, except for
   f[l][k][0][0:2], = real, imaginary part of mode nx/2,k,l,
   where ny/2+1 <= k < ny and 0 <= l < nz, and
   f[l][0][0][0:2] = real, imaginary part of mode nx/2,0,l,
   f[l][ny/2][0][0:2] = real, imaginary part mode nx/2,ny/2,l,
   where nz/2+1 <= l < nz, and
   imag(f[0][0][0][0:2]) = real part of mode nx/2,0,0
   imag(f[0][ny/2][0][0:2]) = real part of mode nx/2,ny/2,0
   imag(f[nz/2][0][0][0:2]) = real part of mode nx/2,0,nz/2
   imag(f[nz/2][ny/2][0][0:2]) = real part of mode nx/2,ny/2,nz/2
   using jpl storage convention, as described in:
   E. Huang, P. C. Liewer, V. K. Decyk, and R. D. Ferraro, "Concurrent
   Three-Dimensional Fast Fourier Transform Algorithms for Coarse-Grained
   Distributed Memory Parallel Computers," Caltech CRPC Report 217-50,
   December 1993.
   written by viktor k. decyk, ucla
local data                                                            */
   int indx1, ndx1yz, nx, nxh, ny, nyh;
   int nz, nzh, nxyz, nxhyz, nyt, nrz, nxhd3, nxhyd;
   int i, j, k, l, n, ll, jj, j1, j2, k1, k2, l1, ns, ns2, km, kmr;
   int i0, i1;
   float complex t1, t2, t3, t4;
   if (isign==0)
      return;
   indx1 = indx - 1;
   ndx1yz = indx1 > indy ? indx1 : indy;
   ndx1yz = ndx1yz > indz ? ndx1yz : indz;
   nx = 1L<<indx;
   nxh = nx/2;
   ny = 1L<<indy;
   nyh = ny/2;
   nz = 1L<<indz;
   nzh = nz/2;
   nxyz = nx > ny ? nx : ny;
   nxyz = nxyz > nz ? nxyz : nz;
   nxhyz = 1L<<ndx1yz;
   nyt = nyi + nyp - 1;
   nxhd3 = 3*nxhd;
   nxhyd = nxhd3*nyd;
   if (isign > 0)
      goto L120;
/* inverse fourier transform */
/* bit-reverse array elements in z */
   nrz = nxhyz/nz;
   for (l = 0; l < nz; l++) {
      ll = nxhyd*l;
      l1 = (mixup[l] - 1)/nrz;
      if (l >= l1)
         continue;
      l1 = nxhyd*l1;
      for (n = nyi-1; n < nyt; n++) {
         i1 = nxhd3*n;
         i0 = i1 + ll;
         i1 += l1;
         for (i = 0; i < nxh; i++) {
            t1 = f[3*i+i1];
            t2 = f[1+3*i+i1];
            t3 = f[2+3*i+i1];
            f[3*i+i1] = f[3*i+i0];
            f[1+3*i+i1] = f[1+3*i+i0];
            f[2+3*i+i1] = f[2+3*i+i0];
            f[3*i+i0] = t1;
            f[1+3*i+i0] = t2;
            f[2+3*i+i0] = t3;
         }
      }
   }
/* finally transform in z */
   nrz = nxyz/nz;
   ns = 1;
   for (l = 0; l < indz; l++) {
      ns2 = ns + ns;
      km = nzh/ns;
      kmr = km*nrz;
      for (k = 0; k < km; k++) {
         k1 = ns2*k;
         k2 = k1 + ns;
         for (j = 0; j < ns; j++) {
            j1 = nxhyd*(j + k1);
            j2 = nxhyd*(j + k2);
            t1 = sct[kmr*j];
            for (n = nyi-1; n < nyt; n++) {
               i1 = nxhd3*n;
               i0 = i1 + j1;
               i1 += j2;
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[3*i+i1];
                  t3 = t1*f[1+3*i+i1];
                  t4 = t1*f[2+3*i+i1];
                  f[3*i+i1] = f[3*i+i0] - t2;
                  f[1+3*i+i1] = f[1+3*i+i0] - t3;
                  f[2+3*i+i1] = f[2+3*i+i0] - t4;
                  f[3*i+i0] += t2;
                  f[1+3*i+i0] += t3;
                  f[2+3*i+i0] += t4;
               }
            }
         }
      }
      ns = ns2;
   }
/* unscramble modes kx = 0, nx/2 */
   for (n = 1; n < nzh; n++) {
      ll = nxhyd*n;
      l1 = nxhyd*nz - ll;
      if (nyi==1) {
         for (jj = 0; jj < 3; jj++) {
            t1 = f[jj+l1];
            f[jj+l1] = 0.5*(cimagf(f[jj+ll] + t1)
                          + crealf(f[jj+ll] - t1)*_Complex_I);
            f[jj+ll] = 0.5*(crealf(f[jj+ll] + t1)
                          + cimagf(f[jj+ll] - t1)*_Complex_I);
         }
      }
      if ((nyi <= (nyh+1)) && (nyt >= (nyh+1))) {
         for (jj = 0; jj < 3; jj++) {
            i1 = nxhd3*nyh;
            i0 = i1 + ll;
            i1 += l1;
            t1 = f[jj+i1];
            f[jj+i1] = 0.5*(cimagf(f[jj+i0] + t1)
                        +   crealf(f[jj+i0] - t1)*_Complex_I);
            f[jj+i0] = 0.5*(crealf(f[jj+i0] + t1)
                          + cimagf(f[jj+i0] - t1)*_Complex_I);
         }
      }
   }
   return;
/* forward fourier transform */
/* scramble modes kx = 0, nx/2 */
L120: for (n = 1; n < nzh; n++) {
      ll = nxhyd*n;
      l1 = nxhyd*nz - ll;
      if (nyi==1) {
         for (jj = 0; jj < 3; jj++) {
            t1 = cimagf(f[jj+l1]) + crealf(f[jj+l1])*_Complex_I;
            f[jj+l1] = conjf(f[jj+ll] - t1);
            f[jj+ll] += t1;
         }
      }
      if ((nyi <= (nyh+1)) && (nyt >= (nyh+1))) {
         for (jj = 0; jj < 3; jj++) {
            i1 = nxhd3*nyh;
            i0 = i1 + ll;
            i1 += l1;
            t1 = cimagf(f[jj+i1]) + crealf(f[jj+i1])*_Complex_I;
            f[jj+i1] = conjf(f[jj+i0] - t1);
            f[jj+i0] += t1;
         }
      }
   }
/* bit-reverse array elements in z */
   nrz = nxhyz/nz;
   for (l = 0; l < nz; l++) {
      ll = nxhyd*l;
      l1 = (mixup[l] - 1)/nrz;
      if (l >= l1)
         continue;
      l1 = nxhyd*l1;
      for (n = nyi-1; n < nyt; n++) {
         i1 = nxhd3*n;
         i0 = i1 + ll;
         i1 += l1;
         for (i = 0; i < nxh; i++) {
            t1 = f[3*i+i1];
            t2 = f[1+3*i+i1];
            t3 = f[2+3*i+i1];
            f[3*i+i1] = f[3*i+i0];
            f[1+3*i+i1] = f[1+3*i+i0];
            f[2+3*i+i1] = f[2+3*i+i0];
            f[3*i+i0] = t1;
            f[1+3*i+i0] = t2;
            f[2+3*i+i0] = t3;
         }
      }
   }
/* first transform in z */
nrz = nxyz/nz;
   ns = 1;
   for (l = 0; l < indz; l++) {
      ns2 = ns + ns;
      km = nzh/ns;
      kmr = km*nrz;
      for (k = 0; k < km; k++) {
         k1 = ns2*k;
         k2 = k1 + ns;
         for (j = 0; j < ns; j++) {
            j1 = nxhyd*(j + k1);
            j2 = nxhyd*(j + k2);
            t1 = conjf(sct[kmr*j]);
            for (n = nyi-1; n < nyt; n++) {
               i1 = nxhd3*n;
               i0 = i1 + j1;
               i1 += j2;
               for (i = 0; i < nxh; i++) {
                  t2 = t1*f[3*i+i1];
                  t3 = t1*f[1+3*i+i1];
                  t4 = t1*f[2+3*i+i1];
                  f[3*i+i1] = f[3*i+i0] - t2;
                  f[1+3*i+i1] = f[1+3*i+i0] - t3;
                  f[2+3*i+i1] = f[2+3*i+i0] - t4;
                  f[3*i+i0] += t2;
                  f[1+3*i+i0] += t3;
                  f[2+3*i+i0] += t4;
               }
            }
         }
      }
      ns = ns2;
   }
   return;
}

/*--------------------------------------------------------------------*/
void cwfft3rx(float complex f[], int isign, int mixup[],
              float complex sct[], int indx, int indy, int indz,
              int nxhd, int nyd, int nzd, int nxhyzd, int nxyzhd) {
/* wrapper function for real to complex fft, with packed data */
/* local data */
   int ny, nz;
   static int nyi = 1, nzi = 1;
/* calculate range of indices */
   ny = 1L<<indy;
   nz = 1L<<indz;
/* inverse fourier transform */
   if (isign < 0) {
/* perform xy fft */
      cfft3rxy(f,isign,mixup,sct,indx,indy,indz,nzi,nz,nxhd,nyd,nzd,
               nxhyzd,nxyzhd);
/* perform z fft */
      cfft3rxz(f,isign,mixup,sct,indx,indy,indz,nyi,ny,nxhd,nyd,nzd,
               nxhyzd,nxyzhd);
   }
/* forward fourier transform */
   else if (isign > 0) {
/* perform z fft */
      cfft3rxz(f,isign,mixup,sct,indx,indy,indz,nyi,ny,nxhd,nyd,nzd,
               nxhyzd,nxyzhd);
/* perform xy fft */
      cfft3rxy(f,isign,mixup,sct,indx,indy,indz,nzi,nz,nxhd,nyd,nzd,
               nxhyzd,nxyzhd);
   }
   return;
}

/*--------------------------------------------------------------------*/
void cwfft3r3(float complex f[], int isign, int mixup[],
              float complex sct[], int indx, int indy, int indz,
              int nxhd, int nyd, int nzd, int nxhyzd, int nxyzhd) {
/* wrapper function for 3 2d real to complex ffts, with packed data */
/* local data */
   int ny, nz;
   static int nyi = 1, nzi = 1;
/* calculate range of indices */
   ny = 1L<<indy;
   nz = 1L<<indz;
/* inverse fourier transform */
   if (isign < 0) {
/* perform xy fft */
      cfft3r3xy(f,isign,mixup,sct,indx,indy,indz,nzi,nz,nxhd,nyd,nzd,
                nxhyzd,nxyzhd);
/* perform z fft */
      cfft3r3z(f,isign,mixup,sct,indx,indy,indz,nyi,ny,nxhd,nyd,nzd,
               nxhyzd,nxyzhd);
   }
/* forward fourier transform */
   else if (isign > 0) {
/* perform z fft */
      cfft3r3z(f,isign,mixup,sct,indx,indy,indz,nyi,ny,nxhd,nyd,nzd,
               nxhyzd,nxyzhd);
/* perform xy fft */
      cfft3r3xy(f,isign,mixup,sct,indx,indy,indz,nzi,nz,nxhd,nyd,nzd,
                nxhyzd,nxyzhd);
   }
   return;
}

/* Interfaces to Fortran */

/*--------------------------------------------------------------------*/
void cdistr3_(float *part, float *vtx, float *vty, float *vtz,
              float *vdx, float *vdy, float *vdz, int *npx, int *npy,
              int *npz, int *idimp, int *nop, int *nx, int *ny, int *nz, 
              int *ipbc) {
   cdistr3(part,*vtx,*vty,*vtz,*vdx,*vdy,*vdz,*npx,*npy,*npz,*idimp,
           *nop,*nx,*ny,*nz,*ipbc);
   return;
}

/*--------------------------------------------------------------------*/
void cgpush3l_(float *part, float *fxyz, float *qbm, float *dt,
               float *ek, int *idimp, int *nop, int *nx, int *ny,
               int *nz, int *nxv, int *nyv, int *nzv, int *ipbc) {
   cgpush3l(part,fxyz,*qbm,*dt,ek,*idimp,*nop,*nx,*ny,*nz,*nxv,*nyv,
            *nzv,*ipbc);
   return;
}

/*--------------------------------------------------------------------*/
void cgpost3l_(float *part, float *q, float *qm, int *nop, int *idimp,
               int *nxv, int *nyv, int *nzv) {
   cgpost3l(part,q,*qm,*nop,*idimp,*nxv,*nyv,*nzv);
   return;
}   

/*--------------------------------------------------------------------*/
void cdsortp3yzl_(float *parta, float *partb, int *npic, int *idimp,
                  int *nop, int *ny1, int *nyz1) {
   cdsortp3yzl(parta,partb,npic,*idimp,*nop,*ny1,*nyz1);
   return;
}

/*--------------------------------------------------------------------*/
void ccguard3l_(float *fxyz, int *nx, int *ny, int *nz, int *nxe,
                int *nye, int *nze) {
   ccguard3l(fxyz,*nx,*ny,*nz,*nxe,*nye,*nze);
   return;
}

/*--------------------------------------------------------------------*/
void caguard3l_(float *q, int *nx, int *ny, int *nz, int *nxe, int *nye,
                int *nze) {
   caguard3l(q,*nx,*ny,*nz,*nxe,*nye,*nze);
   return;
}

/*--------------------------------------------------------------------*/
void cpois33_(float complex *q, float complex *fxyz, int *isign,
              float complex *ffc, float *ax, float *ay, float *az,
              float *affp, float *we, int *nx, int *ny, int *nz,
              int *nxvh, int *nyv, int *nzv, int *nxhd, int *nyhd,
              int *nzhd) {
   cpois33(q,fxyz,*isign,ffc,*ax,*ay,*az,*affp,we,*nx,*ny,*nz,*nxvh,
           *nyv,*nzv,*nxhd,*nyhd,*nzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cwfft3rinit_(int *mixup, float complex *sct, int *indx, int *indy,
                  int *indz, int *nxhyzd, int *nxyzhd) {
   cwfft3rinit(mixup,sct,*indx,*indy,*indz,*nxhyzd,*nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cwfft3rx_(float complex *f, int *isign, int *mixup,
               float complex *sct, int *indx, int *indy, int *indz,
               int *nxhd, int *nyd, int *nzd, int *nxhyzd, int *nxyzhd) {
   cwfft3rx(f,*isign,mixup,sct,*indx,*indy,*indz,*nxhd,*nyd,*nzd,
            *nxhyzd,*nxyzhd);
   return;
}

/*--------------------------------------------------------------------*/
void cwfft3r3_(float complex *f, int *isign, int *mixup,
               float complex *sct, int *indx, int *indy, int *indz,
               int *nxhd, int *nyd, int *nzd, int *nxhyzd, int *nxyzhd) {
   cwfft3r3(f,*isign,mixup,sct,*indx,*indy,*indz,*nxhd,*nyd,*nzd,
            *nxhyzd,*nxyzhd);
   return;
}

