#include "syspara.h"

// Fast Sodium Current (time dependant) */
// gna;    // Max. Conductance of the Na Channel (mS/uF)
// am;     // Na alpha-m rate constant (ms^-1)
// bm;     // Na beta-m rate constant (ms^-1)
// ah;     // Na alpha-h rate constant (ms^-1)
// bh;     // Na beta-h rate constant (ms^-1)
// aj;     // Na alpha-j rate constant (ms^-1)
// bj;     // Na beta-j rate constant (ms^-1)
// x[10]=[Na]i (nai)
// var.nao=[Na]o (nao)

void comp_ina(double x[])
{

	int iV=0;
	double V1,V2,d1,d2;

	V1 = (x[0]+200)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	ina.mss = ina.Tmss[iV]*d2 + ina.Tmss[iV+1]*d1;
	ina.taum = ina.Ttaum[iV]*d2 + ina.Ttaum[iV+1]*d1;
	ina.hss = ina.Thss[iV]*d2 + ina.Thss[iV+1]*d1;
	ina.tauh = ina.Ttauh[iV]*d2 + ina.Ttauh[iV+1]*d1;
	ina.jss = ina.Tjss[iV]*d2 + ina.Tjss[iV+1]*d1;
	ina.tauj = ina.Ttauj[iV]*d2 + ina.Ttauj[iV+1]*d1;

	var.Ena=((R*T)/F)*log(var.nao/x[10]); // [Na]i = x[10],[Na]o = var.nao

	
/*	if(fabs(x[0]+47.13)>0.001){ 
		var.am = 0.32*(x[0]+47.13)/(1.0-exp(-0.1*(x[0]+47.13)));
	} else {
		var.am = 3.2;
	}
	var.bm = 0.08*exp(-x[0]/11.0);

	if (x[0] < -40.0){
		var.ah = 0.135*exp((80.0+x[0])/-6.8);
		var.bh = 3.56*exp(0.079*x[0])+3.1E+5*exp(0.35*x[0]);
		var.aj = (-127140.0*exp(0.244*x[0])-3.474E-5*exp(-0.04391*x[0]))*(x[0]+37.78)/(1.0+exp(0.311*(x[0]+79.23)));
		var.bj = (0.1212*exp(-0.01052*x[0]))/(1.0+exp(-0.1378*(x[0]+40.14)));
	} else {
		var.ah = 0;
		var.bh = 1.0/(0.13*(1.0+exp(-(x[0]+10.66)/11.1)));
		var.aj = 0;
		var.bj = (0.3*exp(-2.535E-7*x[0]))/(1.0+exp(-0.1*(x[0]+32.0)));
	} */

	var.ina = var.gna_max*x[1]*x[1]*x[1]*x[2]*x[3]*(x[0]-var.Ena);
}


// L-type calcium current
//
// ilca; // the L-type Ca channel current (uA/uF)
// d;     // Steady-state value of activation gate d 
// f;     // Steady-state value of inactivation gate f
// fca;     // Ca dependant inactivation gate
// kmca = 0.0006;     // Half-saturation concentration of Ca channel (mM/L)
// x[12] = [Ca]i (cai)
// var.cao = [Ca]o (cao)

void comp_ical(double x[])
{

	int iV=0;
	double V1,V2,d1,d2;

	V1 = (x[0]+200)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	ical.dss = ical.Tdss[iV]*d2 + ical.Tdss[iV+1]*d1;
	ical.taud = ical.Ttaud[iV]*d2 + ical.Ttaud[iV+1]*d1;
	ical.fss = ical.Tfss[iV]*d2 + ical.Tfss[iV+1]*d1;
	ical.tauf = ical.Ttauf[iV]*d2 + ical.Ttauf[iV+1]*d1;
	
	var.Eca=(R*T)/(2*F)*log(var.cao/x[12]);
	var.fca = 1/(1+(x[12]/var.km_ca));
	//var.fca = 1/(1+(x[12]/var.km_ca)*(x[12]/var.km_ca));
	
	//var.ad = (14.98/(16.68*sqrt(2*M_PI)))*exp(-0.5*((x[0]-22.36)/16.68)*((x[0]-22.36)/16.68));
	//var.bd = 0.1471-((5.3/(14.93*sqrt(2*M_PI)))*exp(-0.5*((x[0]-6.27)/14.93)*((x[0]-6.27)/14.93)));

	//var.af = 6.87E-3/(1.0+exp((x[0]-6.1546)/6.12));
	//var.bf = (0.069*exp(-0.11*(x[0]+9.825))+0.011)/(1+exp(-0.278*(x[0]+9.825)))+5.75E-4;

	var.ilca=var.gca_max*x[4]*x[5]*var.fca*(x[0]-var.Eca);

}

// Ito Transient Outward Current
//
// gto_max;    // Maximum conductance of Ito (mS/uF)
// Eto;      // Reversal Potential of Ito
// ar;      // Ito alpha-r rate constant
// br;      // Ito beta-r rate constant
// at;      // Ito alpha-t rate constant
// bt;      // Ito beta-t rate constant

void comp_ito (double x[])
{

	int iV=0;
	double V1,V2,d1,d2;

	V1 = (x[0]+200)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	ito.rss = ito.Trss[iV]*d2 + ito.Trss[iV+1]*d1;
	ito.taur = ito.Ttaur[iV]*d2 + ito.Ttaur[iV+1]*d1;
	ito.tss = ito.Ttss[iV]*d2 + ito.Ttss[iV+1]*d1;
	ito.taut = ito.Ttaut[iV]*d2 + ito.Ttaut[iV+1]*d1;
	
	var.Eto=(R*T/F)*log((0.043*var.nao+var.ko)/(0.043*x[10]+x[11]));

//	var.ar = (0.5266*exp(-0.0166*(x[0]-42.2912)))/(1.0 + exp(-0.0943*(x[0]-42.2912)));
//	var.br = (0.5149*exp(-0.1344*(x[0]-5.0027))+5.186E-5*x[0])/(1.0 + exp(-0.1348*(x[0]-5.186E-5)));

//	var.at = (0.0721*exp(-0.173*(x[0]+34.2531))+5.612E-5*x[0])/(1.0+exp(-0.1732*(x[0]+34.2531)));
//	var.bt = (0.0767*exp(-1.66E-9*(x[0]+34.0235))+1.215E-4*x[0])/(1.0+exp(-0.1604*(x[0]+34.0235)));

	var.ito = var.gto_max*x[6]*x[7]*(x[0]-var.Eto);

}

// Slowly Activating Potassium Current 
// gks_max;   // Channel Conductance of Slowly Activating K Current (mS/uF)
// Eks;   // Reversal Potential of Slowly Activating K Current (mV)
// axs;   // Steady-state value of activation gate xs1
// bxs;   // Steady-state value of activation gate xs2
// prnak = 0.01833; // Na/K Permiability Ratio
// x[10] = [Na]i (nai)
// x[11] = [K]i (ki)
// x[12] = [Ca]i (cai)
// var.nao = [Na]o (nao)
// var.ko = [K]o (ko)
// var.cao = [Ca]o (cao)

void comp_iks (double x[])
{

	int iV=0;
	double V1,V2,d1,d2;

	V1 = (x[0]+200)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	iks.xsss = iks.Txsss[iV]*d2 + iks.Txsss[iV+1]*d1;
	iks.tauxs = iks.Ttauxs[iV]*d2 + iks.Ttauxs[iV+1]*d1;
	
	var.Eks = (R*T/F)*log((var.ko+0.01833*var.nao)/(x[11]+0.01833*x[10]));
	
	//var.axs = 3.0E-3/(1.0+exp((7.44-(x[0]+10))/14.32));
	//var.bxs = 5.87E-3/(1.0+exp((-5.95-(x[0]+10))/-15.82));

	var.iks = var.gks_max*x[8]*x[8]*(x[0]-var.Eks);

}

// Rapidly Activating Potassium Current 
// gkr_max;   // Channel Conductance of Rapidly Activating K Current (mS/uF)
// Ekr;   // Reversal Potential of Rapidly Activating K Current (mV)
// axr;  // Steady-state value of activation gate xr
// bxr;  // Steady-state value of activation gate xr
// rik;  // inward rectification factor of IKs
// x[11] = [K]i (ki)
// var.ko = [K]o (ko)

void comp_ikr (double x[])
{
	
	int iV=0;
	double V1,V2,d1,d2;

	V1 = (x[0]+200)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	ikr.xrss = ikr.Txrss[iV]*d2 + ikr.Txrss[iV+1]*d1;
	ikr.tauxr = ikr.Ttauxr[iV]*d2 + ikr.Ttauxr[iV+1]*d1;
	ikr.rik = ikr.Trik[iV]*d2 + ikr.Trik[iV+1]*d1;
	
	var.Ekr = (R*T/F)*log(var.ko/x[11]);

//	var.axr = (0.005*exp(5.266E-4*(x[0]+4.067)))/(1.0 + exp(-0.1262*(x[0]+4.067)));
//	var.bxr = (0.016*exp(0.0016*(x[0]+65.66)))/(1.0+exp(0.0783*(x[0]+65.66)));

//	var.rik = 1.0/(1.0+exp((x[0]+26.0)/23.0));
	
	//var.ikr =  var.normal_block*var.ikrf*var.gkr_max*var.rik*x[9]*(x[0]-var.Ekr);
	var.ikr =  var.gkr_max*ikr.rik*x[9]*(x[0]-var.Ekr);

}

// Potassium Current (time-independant)
// gk1_max;  // Channel Conductance of inward rectifier Current (mS/uF)
// ak1;      // alpha-ki rate constant of the inactivation gate (ms^-1)
// bk1;      // beta-ki rate constant of the inactivation gate (ms^-1)
// k1_inf;   // inactivation gate of IK1

void comp_ik1 (double x[])
{

	var.Ek1 = var.Ekr;

	var.ak1 = 0.1/(1.0+exp(0.06*(x[0]-(var.Ek1+200))));
	var.bk1 = (3.0*exp(2E-4*(x[0]-var.Ek1+100))+exp(0.1*(x[0]-var.Ek1-10)))/(1.0+exp(-0.5*(x[0]-var.Ek1)));

	var.k1_inf = var.ak1/(var.ak1+var.bk1);

	var.ik1 = var.gk1_max*var.k1_inf*(x[0]-var.Ek1);

}

// Ca Background Current 
// gcab;  // Max. conductance of Ca background (mS/uF)
// Eca;  // Nernst potential for Ca (mV)

void comp_icab (double x[])
{

	var.Ecab = var.Eca;
	var.icab = var.gcab*(x[0]-var.Ecab);

}

// Na Background Current 
// gnab;  // Max. conductance of Ca background (mS/uF)
// Enab;  // Nernst potential for Ca (mV)

void comp_inab (double x[])
{

	var.Enab = var.Ena;
	var.inab = var.gnab*(x[0]-var.Enab);

}

// Sodium-Potassium Pump
// fnak;    // Voltage-dependance parameter of inak 
// sigma;   // [Na]o dependance factor of fnak 
// ibarnak = 1.3; // Max. current through Na-K pump (pA/pF) : control 
// ibarnak = 0.75;// Max. current through Na-K pump (pA/pF) : heart failure 
// kmnai = 10;    // Half-saturation concentration of NaK pump (mM) 
// kmko = 1.5;    // Half-saturation concentration of NaK pump (mM)

void comp_inak (double x[])
{

	double para;

	para = F/(R*T);

	var.sigma = (exp(var.nao/67.3)-1.0)/7.0;
	var.fnak = 1.0/(1.0+0.1245*exp(-0.1*x[0]*para)+0.0365*var.sigma*exp(-x[0]*para));

	var.inak = var.ibarnak*var.fnak*1.0/(1.0+pow(var.kmnai/x[10],1.5))*var.ko/(var.ko+var.kmko);

}

// Sodium-Calcium Exchanger V-S
// knaca = 1000 (pA/pF); // control 
// knaca = 1650 (pA/pF); // heart failure 
// ksat = 0.1;   // the saturation factor of inaca at very negative potentials
// eta = 0.35;   // position of the energy barrier controling voltage dependence of Inaca
// kmna = 82.5 (mM/L); --> 87.5 (mM) in CellML 
// kmca = 1.38 (mM/L);

void comp_inaca (double x[])
{

	double para;
	double u1,u2,u3,u4;

	para = F/(R*T);

	u1 = 1.0/(var.kmna*var.kmna*var.kmna+var.nao*var.nao*var.nao);
	u2 = 1.0/(var.kmca+var.cao);
	u3 = 1.0/(1.0+var.ksat*exp((var.eta-1)*x[0]*para));
	u4 = exp(var.eta*x[0]*para)*x[10]*x[10]*x[10]*var.cao - exp((var.eta-1)*x[0]*para)*var.nao*var.nao*var.nao*x[12];

    var.inaca = var.knaca*u1*u2*u3*u4;

}

void conc_nsr (double x[])

// NSR Ca Ion Concentration Changes 
// iup;      // Ca uptake from myo. to NSR (mM/L/ms)
// ileak;    // Ca leakage from NSR to myo. (mM/L/ms)
// itr;      // Translocation current of Ca ions from NSR to JSR (mM/L/ms)
// x[12] = [Ca]i (cai)
// x[13] = [Ca]_NSR (nsr)
// x[14] = [Ca]_JSR (jsr)

{

	var.ileak = var.kleak*x[13];

	var.iup = var.iupbar*x[12]/(x[12]+var.kmup);

	var.itr = (x[13]-x[14])/var.tautr; 
}

void conc_cai (double x[])

// Myoplasmic Ca Ion Concentration Changes 
// catotal; // Total myoplasmic Ca concentration (mM)
// cmdnbar = 0.050;   // Max. [Ca] buffered in CMDN (mM/L)
// trpnbar = 0.070;   // Max. [Ca] buffered in TRPN (mM/L)
// kmcmdn = 0.00238;  // Equalibrium constant of buffering for CMDN (mM/L)
// kmtrpn = 0.0005;   // Equalibrium constant of buffering for TRPN (mM/L)

{

	double u1,u2,u3,u4,u5,u6;
	
	u1 = (var.kmcmdn+x[12])*(var.kmcmdn+x[12]);
	u2 = (var.kmtrpn+x[12])*(var.kmtrpn+x[12]);
	u3 = var.cmdnbar*var.kmcmdn/u1;
	u4 = var.trpnbar*var.kmtrpn/u2;
	u5 = (var.kmcsqn+x[14])*(var.kmcsqn+x[14]);
	u6 = var.csqnbar*var.kmcsqn/u5;

	var.cai_bufc = 1.0/(1.0+u3+u4);

	var.ca_jsr_bufc = 1.0/(1.0+u6);

	var.csqn = var.csqnbar*(x[14]/(x[14]+var.kmcsqn));
	//if(var.csqn>8.0){
	//	printf("ca_jsr=%e,kmcaqn=%lf,buf_csqn=%lf\n",x[14],var.kmcsqn,var.csqn);
	//}
	
}

void conc_jsr (double x[])

// JSR Ca Ion Concentration Changes 
// tauon = 2;        	// Time constant of activation of Ca release from JSR (ms)
// tauoff = 2;       	// Time constant of deactivation of Ca release from JSR (ms)
// magrel;           	// Magnitude of Ca release
// irelcicr;         	// Ca release from JSR to myo. due to CICR (mM/ms)
// csqnth = 0.7;    	// Threshold for release of Ca from CSQN due to JSR ovreload (mM)
// csqnth = 7.0;    	// Threshold for release of Ca from CSQN due to JSR ovreload (mM)
// gmaxrel = 22;    	// Max. rate constant of Ca release from JSR due to overload (ms^-1)
// grelbarjsrol;     	// Rate constant of Ca release from JSR due to overload (ms^-1)
// greljsrol;        	// Rate constant of Ca release from JSR due to CICR (ms^-1)
// ireljsrol;        	// Ca release from JSR to myo. due to JSR overload (mM/ms)
// swspontan = 0;    	// switch of spontaneous release
// csqnbar = 10;     	// Max. [Ca] buffered in CSQN (mM)
// kmcsqn = 0.8;     	// Equalibrium constant of buffering for CSQN (mM)
// on;               	// Time constant of activation of Ca release from JSR (ms)
// off;              	// Time constant of deactivation of Ca release from JSR (ms)
// dICa;          		// Rate of change of Ca entry
// dICa_new;       		// New rate of change of Ca entry
// ICa_total_old;        // Old rate of change of Ca entry
// x[12] = [Ca]i (cai)
// x[13] = [Ca]_NSR (nsr)
// x[14] = [Ca]_JSR (jsr)
// tcicr = t=0 at time of CICR (ms)
// tjsrol = t=0 at time of JSR overload (ms)

{

	double magrel;
	double grel,greljsrol;
	double t_stok,para;

	para = var.acap/(2.0*var.vmyo*F);
	
	if( -(var.INa_total+var.IK_total+var.ICa_total) > 150 && var.boolien == 0){
		var.boolien = 1;
		var.timer = 0;
		//printf("reset t_cicr.\n");
	}

	if( var.boolien == 1 && var.timer < 2.0){
		var.Cainflux2 += var.dt*(-(var.ilca + var.icab - 2.0*var.inaca)*para);
		//printf("Cainf2=%e\n",var.Cainflux2);
		//printf("timer=%e\n",var.timer);
	} else {
		var.Cainflux2 += 0;
	}
	
	if(var.timer >= 2.0 && var.boolien==1 && var.Cainflux2-var.Cainflux_th > 0){
		var.boolien = 2;
		var.t_cicr = 0.0;
		magrel = (var.Cainflux2-var.Cainflux_th)/(var.km_rel+var.Cainflux2-var.Cainflux_th);
		printf("start CICR. magrel=%e, tcicr=%lf, Grelmax=%lf\n",magrel,var.t_cicr,var.gmaxrel);
	//} else if(var.timer<= 2.0 && var.boolien!=2) {
	//	magrel = 0.0;
	}
	
	//grel = var.gmaxrel*(var.Cainflux2-var.Cainflux_th)/(var.km_rel+var.Cainflux2-var.Cainflux_th)*(1.0-exp(-var.t_cicr/4.0))*exp(-var.t_cicr/4.0);

	if(var.Cainflux2-var.Cainflux_th <= 0 ){
		grel = 0.0;
	} else {
		grel = var.gmaxrel*(var.Cainflux2-var.Cainflux_th)/(var.km_rel+var.Cainflux2-var.Cainflux_th)*(1.0-exp(-var.t_cicr/4.0))*exp(-var.t_cicr/4.0);
		var.dtmp = var.gmaxrel*(var.Cainflux2-var.Cainflux_th)/(var.km_rel+var.Cainflux2-var.Cainflux_th);
	}
	
	var.Irel_cicr = grel*(x[14]-x[12]);
	
	greljsrol = var.gmaxrel_jsr_ol*(1.0-exp(-var.t_jsr_ol/var.tauon))*exp(-var.t_jsr_ol/var.tauoff);
	
	var.Irel_jsr_ol = greljsrol*(x[14]-x[12]);
	
	var.t_cicr += var.dt;
	var.t_jsr_ol += var.dt;
	var.timer += var.dt;
}

