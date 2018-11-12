#include "syspara.h"

void make_ExpTable()
{

	int vindex,kiindex;
	double v,ki;
	double am,bm,ah,bh,aj,bj;
	double ar,br,at,bt;
   	double ad,bd,af,bf;
   	double axr,bxr;
   	double axs,bxs;

	for(vindex=0;vindex<VNMAX;vindex++){

        v = (double)vindex/dvm-200.0;
		
		if(fabs(v+47.13)>0.001){
			am = 0.32*(v+47.13)/(1.0-exp(-0.1*(v+47.13)));
		} else {
			am = 3.2;
		}
		bm = 0.08*exp(-v/11.0);

		ina.Tmss[vindex] = am/(am+bm);
		ina.Ttaum[vindex] = 1.0/(am+bm);

		if(v < -40.0){
			ah = 0.135*exp((80.0+v)/-6.8);
			bh = 3.56*exp(0.079*v)+3.1E+5*exp(0.35*v);
			aj = (-127140.0*exp(0.244*v)-3.474E-5*exp(-0.04391*v))*(v+37.78)/(1.0+exp(0.311*(v+79.23)));
			bj = (0.1212*exp(-0.01052*v))/(1.0+exp(-0.1378*(v+40.14)));
		} else {
			ah = 0.0;
			bh = 1.0/(0.13*(1.0+exp(-(v+10.66)/11.1)));
			aj = 0.0;
			bj = (0.3*exp(-2.535E-7*v))/(1.0+exp(-0.1*(v+32.0)));
		}
		ina.Thss[vindex] = ah/(ah+bh);
		ina.Ttauh[vindex] = 1.0/(ah+bh);
		ina.Tjss[vindex] = aj/(aj+bj);
		ina.Ttauj[vindex] = 1.0/(aj+bj);

		// ito
		ar = (0.5266*exp(-0.0166*(v-42.2912)))/(1.0 + exp(-0.0943*(v-42.2912)));
		br = (0.5149*exp(-0.1344*(v-5.0027))+5.186E-5*v)/(1.0 + exp(-0.1348*(v-5.186E-5)));

		at = (0.0721*exp(-0.173*(v+34.2531))+5.612E-5*v)/(1.0+exp(-0.1732*(v+34.2531)));
		bt = (0.0767*exp(-1.66E-9*(v+34.0235))+1.215E-4*v)/(1.0+exp(-0.1604*(v+34.0235)));

		ito.Trss[vindex] = ar/(ar+br);
		ito.Ttaur[vindex] = 1.0/(ar+br);

		ito.Ttss[vindex] = at/(at+bt);
		ito.Ttaut[vindex] = 1.0/(at+bt);

		// for ical
		ad = (14.98/(16.68*sqrt(2*M_PI)))*exp(-0.5*((v-22.36)/16.68)*((v-22.36)/16.68));
		bd = 0.1471-((5.3/(14.93*sqrt(2*M_PI)))*exp(-0.5*((v-6.27)/14.93)*((v-6.27)/14.93)));
		
		af = 6.87E-3/(1.0+exp((v-6.1546)/6.12));
		bf = (0.069*exp(-0.11*(v+9.825))+0.011)/(1+exp(-0.278*(v+9.825)))+5.75E-4;

		ical.Tdss[vindex] = ad/(ad+bd);
		ical.Ttaud[vindex] = 1.0/(ad+bd);

		ical.Tfss[vindex] = af/(af+bf);
		ical.Ttauf[vindex] = 1.0/(af+bf);

		// for ikr 
		axr = (0.005*exp(5.266E-4*(v+4.067)))/(1.0 + exp(-0.1262*(v+4.067)));
		bxr = (0.016*exp(0.0016*(v+65.66)))/(1.0+exp(0.0783*(v+65.66)));

		ikr.Txrss[vindex] = axr/(axr+bxr);
		ikr.Ttauxr[vindex] = 1.0/(axr+bxr);
		ikr.Trik[vindex] = 1.0/(1.0+exp((v+26.0)/23.0));

		// for iks 
		axs = 3.0E-3/(1.0+exp((7.44-(v+10))/14.32));
		bxs = 5.87E-3/(1.0+exp((-5.95-(v+10))/-15.82));

		iks.Txsss[vindex] = axs/(axs+bxs);
		iks.Ttauxs[vindex] = 1.0/(axs+bxs);

/*
		// ik1 
		ik1.Tk1ss[vindex] = 1.0/(1.0+exp(-(v+2.5538*var.ko+144.59)/(1.5692*var.ko+3.8115)));
		ik1.Ttauk1[vindex] = 122.2/(exp(-(v+127.2)/20.36)+exp((v+236.8)/69.33));
		ik1.Trk1[vindex] = 1.0/(1.0+exp((v+105.8-2.6*var.ko)/9.493));

		// inaca
		var.Thca[vindex] = exp(var.qca*v/var.RTonF);
		var.Thna[vindex] = exp(var.qna*v/var.RTonF);

		// inak 
		inak.Tknai[vindex] = inak.ko_nai*exp((inak.delta*v*F)/(3.0*R*T));
		inak.Tknao[vindex] = inak.ko_nao*exp(((1.0-inak.delta)*v*F)/(3.0*R*T));

		// ikb
		ikb.Txkb[vindex] = 1.0/(1.0+exp(-(v-14.48)/18.34));

		// icab
		icab.Texp[vindex] = exp(v/var.RTon2F);

		// inab
		inab.Texp[vindex] = exp(v/var.RTonF);

*/
	}

}
