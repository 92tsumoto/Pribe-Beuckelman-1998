/* produced by Tsumoto. K 2008.10.27 */

#include "syspara.h"

void val_consts(FILE *fp1)
{
	int i,w;
	double v_old,dvdt,dvdt_new;


	// Cell Geometry */
		var.length = 0.01;	// Length of the cell (cm)
		var.a = 0.0011;		// Radius of the cell (cm)
		var.vcell = 1000*M_PI*var.a*var.a*var.length; // Cell Volume:3.801e-5 (uL)
		printf("vcellm=%e\n",var.vcell);
		var.ageo = 2*M_PI*var.a*(var.a+var.length);  // geometric membrane area: 7.671e-5 (um^2)
		var.acap = var.ageo*2;          // Capacitive membrane area: 1.534e-4 cm^2 (cm^2)
		printf("Cm=%e\n",var.acap);
		var.vmyo = var.vcell*0.68;      // Myoplasm volume (uL) = 68% for Cell volume
		var.vmito = var.vcell*0.26;     // Mitochondria volume (uL) = 26% for cell volume
		var.vsr = var.vcell*0.06;       // SR volume (uL)
		var.vnsr = var.vcell*0.0552;    // NSR volume (uL)
		var.vjsr = var.vcell*0.0048;    // JSR volume (uL)
		var.vcleft = var.vcell*0.12/0.88;  // Cleft volume (uL)
		printf("const=%e\n",var.acap/var.vmyo/F);
		//exit(0);

	// Max conductanve (constant)
		// fast sodium current
		var.gna_max = 16;    // mS/uF
		// L-type calcium current
		var.gca_max = 0.064; // mS/uF

		switch(var.celltype){
			case 0: // original value
				if(var.failing==0){
					// transient outward current
					var.gto_max = 0.3;   // mS/uF
					// inward rectifier potassium current
					var.gk1_max = 2.5;  // mS/uF (control)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 1000; //(pA/pF) // control 
				} else if(var.failing==1){
					// transient outward current
					var.gto_max = 0.191;   // mS/uF : heart failure
					// inward rectifier potassium current
					var.gk1_max = 2.0;  // mS/uF (heart failure)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 1650; //(pA/pF) // heart failure 
				}
				// slow component of delayed rectifier potassium current
				var.gks_max = 0.02;  // mS/uF
				break;
			case 1: // for Endo case
				if(var.failing==0){
					// transient outward current
					var.gto_max = 0.25*0.3;   // mS/uF
					// inward rectifier potassium current
					var.gk1_max = 0.82*2.5;  // mS/uF (control)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 0.72*1000; //(pA/pF) // control 
				} else if(var.failing==1){
					// transient outward current
					var.gto_max = 0.25*0.191;   // mS/uF : heart failure
					// inward rectifier potassium current
					var.gk1_max = 0.82*2.0;  // mS/uF (control)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 0.72*1650; //(pA/pF) // heart failure 
				}
				// slow component of delayed rectifier potassium current
				var.gks_max = 2.08*0.02;  // mS/uF
				break;
			case 2:	// for Mid case
				if(var.failing==0){
					// transient outward current
					var.gto_max = 0.87*0.3;   // mS/uF
					// inward rectifier potassium current
					var.gk1_max = 0.83*2.5;  // mS/uF (control)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 1.08*1000; //(pA/pF) // control 
				} else if(var.failing==1){
					// transient outward current
					var.gto_max = 0.87*0.191;   // mS/uF : heart failure
					// inward rectifier potassium current
					var.gk1_max = 0.83*2.0;  // mS/uF (control)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 1.08*1650; //(pA/pF) // heart failure 
				}
				// slow component of delayed rectifier potassium current
				var.gks_max = 0.52*0.02;  // mS/uF
				break;
			case 3: // for Epi case
				if(var.failing==0){
					// transient outward current
					var.gto_max = 0.3;   // mS/uF
					// inward rectifier potassium current
					var.gk1_max = 1.0*2.5;  // mS/uF (control)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 1.0*1000; //(pA/pF) // control 
				} else if(var.failing==1){
					// transient outward current
					var.gto_max = 0.191;   // mS/uF : heart failure
					// inward rectifier potassium current
					var.gk1_max = 1.0*2.0;  // mS/uF (control)
					// Sodium-Calcium Exchanger V-S
					var.knaca = 1.0*1650; //(pA/pF) // heart failure 
				}
				// slow component of delayed rectifier potassium current
				var.gks_max = 2.8*0.02;  // mS/uF
				break;
		}

	// rapid component of delayed rectifier potassium current
		var.gkr_max = 0.015;  // mS/uF

	// L-type calcium current
		var.km_ca = 0.0006;     // Half-saturation concentration of Ca channel (mM)

	// Ca Background Current 
		if(var.failing==0){
			var.gcab = 0.00085;  // Max. conductance of Ca background (mS/uF) (control)
		} else if(var.failing==1){
			var.gcab = 0.0013;  // Max. conductance of Ca background (mS/uF) (heart failure)
		}

	// Na Background Current 
		if(var.failing==0){
			var.gnab = 0.001;  // Max. conductance of Na background (mS/uF) (control)
		} else if(var.failing==1){
			var.gnab = 0.0;  // Max. conductance of Na background (mS/uF) (heart failure)
		}

	// Sodium-Potassium Pump
		if(var.failing==0){
			var.ibarnak = 1.3;   // Max. current through Na-K pump (pA/pF) (control)
		} else if(var.failing==1){
			var.ibarnak = 0.75;   // Max. current through Na-K pump (pA/pF) (heart failure)
		}
		var.kmnai = 10;    // Half-saturation concentration of NaK pump (mM)
		var.kmko = 1.5;    // Half-saturation concentration of NaK pump (mM)

	// Sodium-Calcium Exchanger V-S
		var.ksat = 0.1;   // the saturation factor of inaca at very negative potentials
		var.eta = 0.35;   // position of the energy barrier controling voltage dependence of Inaca
		var.kmna = 87.5; //(mM/L) 
		//var.kmna = 82.5; //(mM/L) This value is described in the original paper.
		var.kmca = 1.38; //(mM/L)

	// NSR Ca Ion Concentration Changes 
		var.kmup = 0.00092;   // Half-saturation concentration of iup (mM/L)
		if(var.failing!=1){
			var.iupbar = 0.0045; // Max. current through iup channel (mM/L/ms) (control)
		} else {
			var.iupbar = 0.0015; // Max. current through iup channel (mM/L/ms) (heart hailure)
		}
		if(var.failing!=1){
			var.kleak = 0.00026; // Rate constant of Ca leakage from NSR (ms^-1) (control)
		} else {
			var.kleak = 0.00017; // Rate constant of Ca leakage from NSR (ms^-1) (heart failure)
		}

	// Translocation of Ca Ions from NSR to JSR
		var.tautr = 180;      // Time constant of Ca transfer from NSR to JSR (ms)
	
	// Ca buffers in the Myoplasm: Troponin (TRPN) and Calmodulin (CMDN) 
		var.cmdnbar = 0.050;   // Max. [Ca] buffered in CMDN (mM/L)
		var.trpnbar = 0.070;   // Max. [Ca] buffered in TRPN (mM/L)
		var.kmcmdn = 0.00238;  // half-saturation concentration of CMDN (mM/L)
		var.kmtrpn = 0.0005;   // half-saturation concentration of TRPN (mM/L)

	// Ca buffers in JSR: Calsequestrin (CSQN)
		var.csqnbar = 10;     // Max. [Ca] buffered in CSQN (mM/L)
		var.kmcsqn = 0.8;     // half-saturation concentration of CSQN (mM/L)
		
		//var.trpn = 0.0143923;
		//var.cmdn = 0.00257849;
		//var.csqn = 6.97978;
	
	// JSR Ca Ion Concentration Changes 
		var.tauon = 4.0;        // Time constant of activation of Ca release from JSR (ms)
		var.tauoff = 4.0;       // Time constant of deactivation of Ca release from JSR (ms)
		//var.csqnth = 0.7;    	// orginal value. Threshold for release of Ca from CSQN due to JSR ovreload (mM)
		//var.csqnth = 7.85;    		// But, caqnth = 7.0 ? for the multipliering value of csqnbar
		var.csqnth = 8.75;    		// But, caqnth = 7.0 ? for the multipliering value of csqnbar
		var.gmaxrel = 22;    	// Max. rate constant of Ca release from JSR due to overload (ms^-1)
		var.gmaxrel_jsr_ol = 0; // Rate constant of Ca release from JSR due to overload (ms^-1)
		var.swspontan = 0;    	// switch of spontaneous release
		var.km_rel = 0.0008;

	// Extracellular Ion Concentrations 
		var.nao=138;
		var.ko=4.0;
		var.cao=2.0;

	// Another parameter initial setting
		var.t_cicr = 25;
		var.t_jsr_ol = 25;
		var.timer = 25;
		var.boolien = 0;
		var.Ca_total_old = 0;
		var.Cainflux2 = 0.0;
		var.Cainflux_th = 5e-6;

		printf("Istim=%lf\n",var.Istim_base);
		printf("csqn=%lf\n",var.csqn);

}

