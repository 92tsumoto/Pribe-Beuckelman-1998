/* produced by Tsumoto. K 2008.10.27 */

#include <string.h>
#include <stdlib.h>
#include "syspara.h"

int mode = 1;
int P = 2;
FILE *fopen(), *fpin, *fp0, *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
int beats = 30;

typedef double Number;

main(argc,argv)
int argc;
char **argv;
{
	int i,w;
	int ii=0;
	double x[NN];
	double t = 0.0;
	double time;
	double h;
	double v_old,dvdt,dvdt_new;
	double t_stok;
	double base_vm;
	char *tmpname;
	char cmd[BUFSIZ];
	double tend;

/* Action Potential Duration and Max. Info */
	//double vmax [beats] ; // Max. Voltage (mV)
	//double dvdtmax [beats] ; // Max. dv/dt (mV/ms)
	double *vmax ; // Max. Voltage (mV)
	double *dvdtmax ; // Max. dv/dt (mV/ms)
	double *dvdtmax2 ; // Max. dv/dt (mV/ms)
	//double apd [beats] ; // Action Potential Duration
	double *apd90; // Action Potential Duration
	double *apd50; // Action Potential Duration
	double *apd20; // Action Potential Duration
	//double toneapd [beats] ; // Time of dv/dt Max.
	double *toneapd; // Time of dv/dt Max.
	//double ttwoapd [beats] ; // Time of 90% Repolarization
	double *ttwoapd90; // Time of 90% Repolarization
	double *ttwoapd50; // Time of 50% Repolarization
	double *ttwoapd20; // Time of 20% Repolarization
	//double rmbp [beats] ; // Resting Membrane Potential
	double *rmbp; // Resting Membrane Potential
	//double nair [beats] ; // Intracellular Na At Rest
	//double cair [beats] ; // Intracellular Ca At Rest
	//double kir [beats] ; // Intracellular K At Rest
	double *nair; // Intracellular Na At Rest
	double *cair; // Intracellular Ca At Rest
	double *kir ; // Intracellular K At Rest
	double caimax [beats] ; // Peak Intracellular Ca
	
	vmax=(Number *)calloc(beats,sizeof(Number));
	dvdtmax=(Number *)calloc(beats,sizeof(Number));
	dvdtmax2=(Number *)calloc(beats,sizeof(Number));
	apd90=(Number *)calloc(beats,sizeof(Number));
	apd50=(Number *)calloc(beats,sizeof(Number));
	apd20=(Number *)calloc(beats,sizeof(Number));
	toneapd=(Number *)calloc(beats,sizeof(Number));
	ttwoapd90=(Number *)calloc(beats,sizeof(Number));
	ttwoapd50=(Number *)calloc(beats,sizeof(Number));
	ttwoapd20=(Number *)calloc(beats,sizeof(Number));
	rmbp=(Number *)calloc(beats,sizeof(Number));
	nair=(Number *)calloc(beats,sizeof(Number));
	cair=(Number *)calloc(beats,sizeof(Number));
	kir=(Number *)calloc(beats,sizeof(Number));
	if(vmax==NULL || dvdtmax==NULL || apd90==NULL || apd50==NULL || apd20==NULL
	|| toneapd==NULL || ttwoapd90==NULL || ttwoapd50==NULL || ttwoapd20==NULL 
	|| rmbp==NULL || nair==NULL || cair==NULL || kir==NULL) exit(1);
//int i; // Stimulation Counter

	tmpname = "temp";

	sprintf(cmd, "/usr/bin/cpp -P %s > %s", argv[1],tmpname);
	if(system(cmd) == -1){
		fprintf(stderr,"cannot open %s\n",argv[1]);
		exit(1);
	}
	if((fpin=fopen(tmpname,"r"))==NULL){
		fprintf(stderr,"cannot open %s\n",argv[1]);
		exit(1);
	}
	if ((fp1 = fopen("para.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp2 = fopen("data.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp3 = fopen("ndata.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp4 = fopen("current.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp5 = fopen("ikr_act.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp6 = fopen("dvdt.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}

	input_para(fpin);

	if (var.write){
		if ((fp0 = fopen(argv[2],"w"))==NULL){
			fprintf(stderr, "%s cannot open.\n",argv[2]);
			exit(-1);
		}
	}

	xhplot(WINDOW, 700.0, 700.0, WHITE);
	xhplot(DIRECT, 0.0, 0.0, WHITE);

	for (ii = 0; ii < var.datas; ii++){
		long j;
		time = 0.0;
		tend = var.tend[ii];
		for (i = 0; i < NN; i++){ 
			x[i] = var.x0[ii][i];
		}
		if (var.half){
			h = M_PI / var.m;
		}
		else {
			h = 1.0 / var.m;
		}
		h *= var.tsign[ii];
		xddp.line_wid = var.line_wid[ii];
		xhplot(LINEATT,0,0,WHITE);

		// initial values input.
		val_consts(fp1);
		printf("exit consts\n");

		// initial values input.
		initial_mem();
		printf("exit memory initialization\n");

		// Tablize exp functions.       
		printf("start tablization\n");
		make_ExpTable();
		printf("finished tablization\n");

		// Initialization time
		time -= h;
		var.dt = h;
		var.beat = 0;
		var.dvdt = 0;
		var.max_flag = 0;

		// unaffected fraction (without facilitation)
		//var.normal_block = 1/(1+pow((var.drug_concentration/var.ic50),var.hillc));
		//kb = 1/(1+pow((var.k1/0.00001656),1.0857));
		
		ii = 0;
		
		for (var.beat=0; var.beat < beats; var.beat++){
			eventloop(fp1,&mode,&P,x);
			
			var.boolien = 0;
			var.Cainflux2 = 0.0;

			if(var.beat == beats-1){
				var.l = 2.0*var.BCL;
			} else {
				var.l = var.BCL;
			}

			for (j = 0; j< (var.m * var.l ); j++){
				t = h*j;
				time += h;

				if ( time-(var.BCL*var.beat+50.0) >= 0.0 && time-(var.BCL*var.beat+50.0) < h ){
					//var.boolien = 0;
					apd90[var.beat] =0; apd50[var.beat] =0; apd20[var.beat] =0;
					toneapd[var.beat] =0;
					ttwoapd90[var.beat] =0; ttwoapd50[var.beat] =0; ttwoapd20[var.beat] =0;
					rmbp[var.beat] =x[0]; nair[var.beat] = x[10]; kir[var.beat] = x[11]; cair[var.beat] = x[12];
					caimax[var.beat] = x[12];
					vmax[var.beat] = 0.0; dvdtmax[var.beat] = -100.0; dvdtmax2[var.beat] = -100.0;

					printf("%d apd=%lf rest=%lf\n",var.beat,apd90[var.beat-1],rmbp[var.beat]);
					printf("time=%lf,Istim=%lf\n",time,var.Istim);
					printf("dvdtmax[%d]=%lf\n",var.beat,dvdtmax[var.beat]);
					//printf("block ratio=%lf\n",var.normal_block);
				}
				
				if (time-(var.BCL*var.beat+50.0) >= 0.0 && time-(var.BCL*var.beat+50.0) < 0.7 ){
					var.Istim = var.Istim_base;
					if(time-(var.BCL*var.beat+50.0) <= h) printf("time=%lf,Istim=%lf\n",time,var.Istim);
				} else {
					var.Istim = 0;
				}

				if (fabs(time) > tend &&  tend != 0.0) break;
				v_old = x[0];

				eular(NN,h,x,t);

				if(var.beat>=0){
					if(var.dvdt > 0 && var.max_flag==0){
						var.max_flag=1;
					} else if(var.dvdt < 0 && var.max_flag==1){
						var.max_flag=2;
					} else if(var.dvdt > 0 && var.max_flag==2){
						var.max_flag=3;
					} else if(var.dvdt < 0 && var.max_flag==3){
						var.max_flag=0;
					}
					if (x[0] > vmax[var.beat] && var.max_flag==3)
						vmax[var.beat] = x[0];
					if (x[12] > caimax[var.beat] )
						caimax[var.beat] = x[12];
					if (var.dvdt > dvdtmax[var.beat] ){
						dvdtmax[var.beat] = var.dvdt;
						toneapd[var.beat] = time;
					}
					if (time-(var.BCL*var.beat+100.0) >= 0.0 ){
						if (var.dvdt > dvdtmax2[var.beat] ){
							dvdtmax2[var.beat] = var.dvdt;
						}
					}
					//base_vm=vmax[var.beat]-rmbp[var.beat];
					base_vm=vmax[var.beat]-(-85.0);
					if (var.dvdt < 0 && x[0] >= (vmax[var.beat] -0.9*base_vm ) )
						ttwoapd90[var.beat] = time;
					if (var.dvdt < 0 && x[0] >= (vmax[var.beat] -0.5*base_vm ) )
						ttwoapd50[var.beat] = time;
					if (var.dvdt < 0 && x[0] >= (vmax[var.beat] -0.2*base_vm ) )
						ttwoapd20[var.beat] = time;
				}
				
				if (var.csqn >= var.csqnth && var.t_jsr_ol > 50.0){
					var.gmaxrel_jsr_ol = 3;
					t_stok = var.t_jsr_ol;
					var.t_jsr_ol = 0.0;
					printf("resrt t_jsr_ol at %lf\n",t_stok);
				}

				if (var.pflag) orbit(&mode,x,var.dvdt);

				//if (time>= (beats-3)*var.BCL && time < beats*var.BCL){
				if (time>= (beats-5)*var.BCL){
				//if (time>= 0.0){
					fprintf(fp2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %e %e %lf\n",
							time,x[0],var.Cainflux2,var.I_all,x[1],x[2],x[3],x[9],
							var.Irel_jsr_ol,x[10],x[11],x[12],x[13],x[14]);
					fprintf(fp4,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
							time,x[0],var.ina,var.ilca,var.ito,var.ikr,var.iks,var.ik1,var.inak,var.inaca,var.inab,var.icab);
					fprintf(fp6,"%lf %lf\n",time,var.dvdt);
				}
				
				var.dvdt = (x[0]-v_old)/h;

			}

			draw_p(&mode,P,x,var.dvdt);
			mouse(&mode,x,var.dvdt);
			if (fabs(time) > tend &&  tend != 0.0) break;

		}

		for(w=0;w<beats;w++){
			apd90[w] = ttwoapd90 [w] -toneapd [w] ;
			apd50[w] = ttwoapd50 [w] -toneapd [w] ;
			apd20[w] = ttwoapd20 [w] -toneapd [w] ;
			fprintf(fp3,"%d\t%g\t%g\t%lf\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%e\t%e\t%g\n",w,
						vmax[w],dvdtmax[w],dvdtmax2[w],apd90[w],apd50[w],apd20[w],toneapd[w],ttwoapd90[w],ttwoapd50[w],ttwoapd20[w],nair[w],kir[w],cair[w],caimax[w],rmbp[w]);
			printf("%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %e %e %lf\n",w,
						vmax[w],dvdtmax[w],dvdtmax2[w],apd90[w],apd50[w],apd20[w],toneapd[w],ttwoapd90[w],ttwoapd50[w],ttwoapd20[w],nair[w],kir[w],cair[w],caimax[w],rmbp[w]);
		}

		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
		fclose(fp4);
		fclose(fp5);
		fclose(fp6);
		free(vmax);free(dvdtmax);free(dvdtmax2);free(apd90);free(apd50);free(apd20);
		free(toneapd);free(ttwoapd90);free(ttwoapd50);free(ttwoapd20);
		free(rmbp);free(nair);free(cair);free(kir);
		closed_mem();

	}
}

