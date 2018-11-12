//#ifndef __SYSPARA_H_INCLUDE 
//#define __SYSPARA_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "mkl.h"
#include "./include/xhplot.h"

#define NN 15
#define BUF 100
#define NUM 20

#define R 8314.462175 //(J/K/mM)=(C*V/K/mM)
#define F 96485.33771638995 // (C/mol)
#define T 310.15 // (K)
//#define R 8.314462175	// (J/K/M)
//#define F 96.485336521 // (C/mM)
//#define T 310.15 // (K)

#define VNMAX 400*5+1
#define dvm 5

struct varstruct {

    int datas;
    int line_wid[NUM];
	
	int n,failing,max_flag;
	double dtmp; // not use
	double dvdt,Istim;

	// Drug concentration for Nifekalant
	//double drug_concentration;

	// Cell type switch
	int celltype;

	// Cell Geometry
	double length,a,vcell,ageo,acap,vmyo,vmito,vsr,vnsr,vjsr,vcleft;

	// Extracellular Ion concentrations
	double nao,ko,cao;

	// Fast sodium current
	double gna_max,Ena,ina;

	// L-type calcium current
	double ilca,gca_max,fca,km_ca,Eca;
	
	// Ito Transient Outward Current
	double ito,gto_max,Eto;

	// Slowly activating potassium current
	double iks,gks_max,Eks;

	// Rapidly activating potassium current
	double ikr,gkr_max,Ekr;
	
	// Inward Rectifier current
	double ik1,gk1_max,Ek1,ak1,bk1,k1_inf;

	// Ca Background Current
	double gcab,Ecab,icab;

	// Na Background Current
	double gnab,Enab,inab;

	// Sodium-Potassium Pump
	double fnak,sigma,ibarnak,kmnai,kmko,inak;
	
	// Sodium-Calcium Exchanger V-S
	double ksat,eta,kmna,kmca,knaca,inaca;

	// Total Ion currents 
	double INa_total, IK_total, ICa_total, I_all;
	
	// Ca ion influx 
	double Cainflux2, Cainflux2_new, Cainflux_th;
	double dICa_total_new,ICa_total_old,dICa_total;
	
	// NSR Ca Ion Concentration Changes
	double iup,ileak,kleak;      // Ca uptake from myo. to NSR (mM/ms)
	double kmup,iupbar,nsrbar;

	// JSR Ca Ion Concentration Changes
	double Irel_cicr,Irel_jsr_ol;
	int boolien;
	double gmaxrel,km_rel;
	double gmaxrel_jsr_ol,tauon,tauoff;
	double csqnbar,kmcsqn,csqn,csqnth;
	double t_cicr,t_jsr_ol,timer;
	double ca_jsr_bufc,cai_bufc,swspontan;

	// test variable
	double dt;

	// Translocation of Ca Ions from NSR to JSR
	double tautr,itr;

	// Ca concentration
	double cmdnbar,trpnbar,kmtrpn,kmcmdn;
	double trpn,cmdn;
	double Ca_total, Ca_total_old;

	// Base Currnt Stimulus
	double Istim_base;

	// Sttimulus parameters
	double BCL;  // Base cycle length = stimulus period
	int beat; // Number of stimulus


	// debug variable
	double ca_pre,dca_now;

    int m;
    int l;

    double x0[NUM][NN];
    double tsign[NUM];
    double tend[NUM];

    int pflag;
    int write, graph;
    int write0;
    int half;

} var;

struct inastruct {
	double *Tmss,*Ttaum;
	double *Thss,*Ttauh;
	double *Tjss,*Ttauj;

	double mss,taum,hss,tauh,jss,tauj;

} ina;

struct icalstruct {
	double *Tdss,*Ttaud;
	double *Tfss,*Ttauf;

	double dss,taud,fss,tauf;

} ical;

struct itostruct {
	double *Trss,*Ttaur;
	double *Ttss,*Ttaut;

	double rss,taur,tss,taut;

} ito;

struct ikrstruct {
	double *Txrss,*Ttauxr,*Trik;

	double xrss,tauxr,rik;

} ikr;

struct iksstruct {
	double *Txsss,*Ttauxs;

	double xsss,tauxs;

} iks;

void eular(int n,double h,double x[],double t);

void function(double x[],double f[],double t);

void input_para(FILE *);
void initial_mem();
void closed_mem();

void val_consts(FILE *);
void eventloop(FILE *, int *mode, int *P, double m[]);

void orbit(int *mode, double m[], double x2);

void draw_p(int *mode, int P, double x[], double x2);

void mouse(int *mode, double x[], double x2);

void comp_ina(double x[]);
void comp_ical(double x[]);
void comp_ikr(double x[]);
void comp_ik1(double x[]);
void comp_iks(double x[]);
void comp_ito(double x[]);
void comp_inaca(double x[]);
void comp_inak(double x[]);
void comp_insca(double x[]);
void comp_icab(double x[]);
void comp_inab(double x[]);
void comp_iconcent (double x[]);
void comp_iconcent2 (double x[]);
void conc_nsr(double x[]);
void conc_jsr(double x[]);
void conc_itr (double x[]);
void conc_cai (double x[]);
void conc_cleft (double x[]);
void track (double x[]);
void aptrack (double x[]);

main(int argc,char **argv);
