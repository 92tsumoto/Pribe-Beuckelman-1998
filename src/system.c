#include "syspara.h"

void function(double x[],double f[],double t)
{
   	double f0,k1,k2,volrat_nsr,volrat_jsr; 
	
	k1= var.acap/var.vmyo/F;
	k2= var.acap/var.vmyo/F/2.0;
	volrat_nsr = var.vnsr/var.vmyo;
	volrat_jsr = var.vjsr/var.vmyo;

	comp_ina(x);
	comp_ical(x);
	comp_ito(x);
	comp_ikr(x);
	comp_iks(x);
	comp_ik1(x);
	comp_inak(x);
	comp_inaca(x);
	comp_icab(x);
	comp_inab(x);
	conc_nsr(x);
	conc_cai(x);
	conc_jsr(x);

	var.I_all = var.INa_total+var.IK_total+var.ICa_total;
	var.INa_total = var.ina + var.inab + 3.0*var.inak + 3.0*var.inaca;
	var.IK_total = var.ikr + var.iks + var.ik1 - 2.0*var.inak + var.ito + var.Istim;
	var.ICa_total = var.ilca + var.icab - 2.0*var.inaca;

	f[0] = -(var.INa_total+var.IK_total+var.ICa_total);
	//f[1] = var.am*(1.0 - x[1]) - var.bm*x[1]; // m 
	//f[2] = var.ah*(1.0 - x[2]) - var.bh*x[2]; // h
	//f[3] = var.aj*(1.0 - x[3]) - var.bj*x[3]; // j
	f[1] = (ina.mss - x[1])/ina.taum; // m: activation for Ina
	f[2] = (ina.hss - x[2])/ina.tauh; // h: inactivation for Ina
	f[3] = (ina.jss - x[3])/ina.tauj; // j: slowly inactivation for Ina

	//f[4] = var.ad*(1.0 - x[4]) - var.bd*x[4];
	//f[5] = var.af*(1.0 - x[5]) - var.bf*x[5];
	f[4] = (ical.dss - x[4])/ical.taud; // d: activation for L-type Ca channel
	f[5] = (ical.fss - x[5])/ical.tauf; // f: inactivation for L-type Ca channel
	//f[6] = var.ar*(1.0 - x[6]) - var.br*x[6];
	//f[7] = var.at*(1.0 - x[7]) - var.bt*x[7];
	f[6] = (ito.rss - x[6])/ito.taur; // r: activation for Ito
	f[7] = (ito.tss - x[7])/ito.taut; // t: inactivation for Ito

	//f[8] = var.axs*(1.0 - x[8]) - var.bxs*x[8];
	f[8] = (iks.xsss - x[8])/iks.tauxs; // xs: activation for Iks 
	//f[9] = var.axr*(1.0 - x[9]) - var.bxr*x[9];         // 
	f[9] = (ikr.xrss - x[9])/ikr.tauxr; // xr: activation for Ikr 
	f[10] = -var.INa_total*k1;
	f[11] = -var.IK_total*k1;
	f[12] = var.cai_bufc*(-var.ICa_total*k2+(var.ileak-var.iup)*volrat_nsr+(var.Irel_cicr+var.Irel_jsr_ol)*volrat_jsr);
	f[13] = var.iup - var.ileak - var.itr*var.vjsr/var.vnsr;
	f[14] = var.ca_jsr_bufc*(var.itr - var.Irel_cicr - var.Irel_jsr_ol);

}


