#include <global.h>
#include <muscleFactory.h>

void PUT_WEIGHTS(PHILOSOPH* p ){

	pthread_mutex_lock(&mutex);

	depot.five_kg += p->weights->five_kg;
	depot.three_kg += p->weights->three_kg;
	depot.two_kg += p->weights->two_kg;

	p->weights->five_kg = 0;
	p->weights->three_kg = 0;
	p->weights->two_kg = 0;

	pthread_mutex_unlock(&mutex);
}


int GET_WEIGHTS(PHILOSOPH* p ){
	int ret=0;

	if(p->weight_for_training==6){
		if(depot.three_kg>=2){
			ret=1;
			depot.three_kg-=2;
			
			p->weights->five_kg = 0;
			p->weights->three_kg = 2;
			p->weights->two_kg = 0;
		}
		else if(depot.two_kg>=3){
			depot.two_kg-=3;
			ret=1;
			
			p->weights->five_kg = 0;
			p->weights->three_kg = 0;
			p->weights->two_kg = 3;
		}
	}

	// 1x5 + 1x3, 2x3 + 1x2, 4x2
	if(p->weight_for_training==8){
		if(depot.five_kg>=1 && depot.three_kg>=1){
			ret=1;
			depot.five_kg-=1;
			depot.three_kg-=1;
			
			p->weights->five_kg = 1;
			p->weights->three_kg = 1;
			p->weights->two_kg = 0;
		}
		else if(depot.three_kg>=2 && depot.two_kg>=1){
			ret=1;
			depot.three_kg-=2;
			depot.two_kg-=1;
			
			p->weights->five_kg = 0;
			p->weights->three_kg = 2;
			p->weights->two_kg = 1;
		}
		else if(depot.two_kg>=4){
			depot.two_kg-=4;
			ret=1;
			
			p->weights->five_kg = 0;
			p->weights->three_kg = 0;
			p->weights->two_kg = 4;
		}
	}

	// 2x5+1x2, 1x5+1x3+2x2, 4x3, 2x3+3x2, 
	if(p->weight_for_training==12){
		if(depot.five_kg>=2 && depot.two_kg>=1){
			ret=1;
			depot.five_kg-=2;
			depot.two_kg-=1;
			
			p->weights->five_kg = 2;
			p->weights->three_kg = 0;
			p->weights->two_kg = 1;
		}
		else if(depot.five_kg>=1 && depot.three_kg >= 1 && depot.two_kg>=2){
			ret=1;
			depot.five_kg-=1;
			depot.three_kg-=1;
			depot.two_kg-=2;
			
			p->weights->five_kg = 1;
			p->weights->three_kg = 1;
			p->weights->two_kg = 2;
		}
		else if(depot.three_kg>=4){
			ret=1;
			depot.three_kg-=4;
			
			p->weights->five_kg = 0;
			p->weights->three_kg = 4;
			p->weights->two_kg = 0;
		}
		else if(depot.three_kg>=2 && depot.two_kg>=3){
			ret=1;
			depot.three_kg-=2;
			depot.two_kg-=3;
			
			p->weights->five_kg = 0;
			p->weights->three_kg = 3;
			p->weights->two_kg = 2;
		}
	}

	// 2x5+2x2, 1x5+3x3, 1x5+1x3+3x2, 4x3+1x2 
	if(p->weight_for_training==14){
		if(depot.five_kg>=2 && depot.two_kg>=2){
			ret=1;
			depot.five_kg-=2;
			depot.two_kg-=2;
			
			p->weights->five_kg = 2;
			p->weights->three_kg = 0;
			p->weights->two_kg = 2;
		}
		else if(depot.five_kg>=1 && depot.three_kg >= 3){
			ret=1;
			depot.five_kg-=1;
			depot.three_kg-=3;
			depot.two_kg-=0;
			
			p->weights->five_kg = 1;
			p->weights->three_kg = 3;
			p->weights->two_kg = 0;
		}
		else if(depot.five_kg>=1 && depot.three_kg >= 1 && depot.two_kg>=3){
			ret=1;
			depot.five_kg-=1;
			depot.three_kg-=1;
			depot.two_kg-=3;
			
			p->weights->five_kg = 1;
			p->weights->three_kg = 1;
			p->weights->two_kg = 3;
		}
		else if(depot.three_kg>=4 && depot.two_kg>=1){
			ret=1;
			depot.three_kg-=4;
			depot.two_kg-=1;
			
			p->weights->five_kg = 0;
			p->weights->three_kg = 4;
			p->weights->two_kg = 1;
		}
	}

	return ret;
}

// WEIGHTS GET_WEIGHTS(int value ){

// 	//printf("\0",value);

//     WEIGHTS output;
// 	WEIGHTS depot_clone;
// 	int* slot;
// 	int* mySlot;
// 	int slotWeight;
// 	int result;
// 	int modulo;
// 	int weight;
// 	int sum;
	
// 	int k;
// 	while(k<3 && sum!=value){

// 		output.five_kg = 0;
// 		output.three_kg = 0;
// 		output.two_kg = 0;

// 		weight = value;
// 		depot_clone = depot;

// 		if(k==1){
// 			depot_clone.five_kg=0;
// 		}

// 		if(k==2){
// 			depot_clone.five_kg=0;
// 			depot_clone.three_kg=0;
// 		}

// 		int i;
// 		for (i = 0; i < 3; i++)
// 		{
// 			if(i==0){
// 				slot = &depot_clone.five_kg;
// 				slotWeight=5;
// 				mySlot = &output.five_kg;
// 			}

// 			if(i==1){
// 				slot = &depot_clone.three_kg;
// 				slotWeight=3;
// 				mySlot = &output.three_kg;
// 			}

// 			if(i==2){
// 				slot = &depot_clone.two_kg;
// 				slotWeight=2;
// 				mySlot = &output.two_kg;
// 			}

// 			if(*slot!=0){

// 				result = weight/slotWeight;

// 				while(result>=1){

// 					modulo = weight%slotWeight;

// 					if(result!=0 && weight-slotWeight*result!=1 
// 						&& weight>=slotWeight && *slot-result>=0){

// 						*mySlot = result;
// 						*slot = *slot-result;
					
// 						if(modulo!=0){
// 							weight = weight-slotWeight*result;
// 						} 
// 						else{
// 							//finish
// 							weight=0;
// 							sum = output.five_kg*5+output.three_kg*3+output.two_kg*2;
// 							break;
// 						}
// 					}
// 					else{
// 						result--;
// 					}
// 				}
// 			}
// 		}
// 		k++;
// 	}

// 	if(sum==value){
// 		depot.five_kg  -= output.five_kg;
// 		depot.three_kg -= output.three_kg;
// 		depot.two_kg   -= output.two_kg;

// 		weights_avialable=1;
// 	}
// 	else{
// 		output.five_kg = 0;
// 		output.three_kg = 0;
// 		output.two_kg = 0;
// 	}

// 	return output;
// }

