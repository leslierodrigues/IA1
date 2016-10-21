unsigned manhattan0[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned manhattan1[16] = {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5};
unsigned manhattan2[16] = {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4};
unsigned manhattan3[16] = {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3};
unsigned manhattan4[16] = {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5};
unsigned manhattan5[16] = {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4};
unsigned manhattan6[16] = {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3};
unsigned manhattan7[16] = {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2};
unsigned manhattan8[16] = {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4};
unsigned manhattan9[16] = {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3};
unsigned manhattan10[16] = {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2};
unsigned manhattan11[16] = {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1};
unsigned manhattan12[16] = {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3};
unsigned manhattan13[16] = {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2};
unsigned manhattan14[16] = {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1};
unsigned manhattan15[16] = {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0};

unsigned* manhattan[16] = {manhattan0,manhattan1,manhattan2,manhattan3,manhattan4,manhattan5,manhattan6,manhattan7,manhattan8,manhattan9,manhattan10,manhattan11,manhattan12,manhattan13,manhattan14,manhattan15};

unsigned int heuristic(state_t *state){

	unsigned int tam = sizeof(state->vars)/sizeof(state->vars[0]);
	unsigned int h = 0;

	for(unsigned int i=0; i< tam; i++){
			h += manhattan[state->vars[i]][i];
	}
	
    return h;

}