
//  polystep.c

#include "m_pd.h"


static t_class *polystep_class;


typedef struct _polystep {
    t_object    x_obj;
    t_inlet     *in_notes, *in_aux, *in_knob_playmode, *in_knob_recordmode, *in_ppn;
    t_outlet    *out_notes, *out_B, *out_messages;
} t_polystep;



//Reset the count to start at 0
void polystep_resetCount(t_polystep *x){
    //Initialize the counts to start at 0 again
    x->init_count = 0;
    x->current_count = x->init_count;
}

//Perform on bang
void polystep_onBangMsg(t_polystep *x){
    post("[polystep ] is ready to go");
    outlet_bang(x->out_A);
    outlet_bang(x->out_B);
    outlet_bang(x->out_synch);
    outlet_float(x->out_count, 1);
}

void polystep_onResetMsg(t_polystep *x){
    polystep_resetCount(x);
}

//Handle lists: [A B(
void polystep_onListMsg(t_polystep *x, t_symbol *s, t_int argc, t_atom *argv){
    switch(argc){
            //Lists must have two arguments (to set both A and B); otherwise we'll throw an error
        case 2:
            //Set mod_A and mod_B
            polystep_setMods(x, atom_getfloat(argv), atom_getfloat(argv+1));
            
            //Reset the counts
            polystep_resetCount(x);
            break;
        default:
            error("[polystep ]: two arguments are needed to set a new ratio");
    }
}

//Set A part of ratio; however, don't reset
void polystep_onSet_A(t_polystep *x, t_floatarg f){
    //New number for A of A:B
    polystep_setMods(x, f, x->mod_B);
}

//Set B part of ratio; however, don't reset
void polystep_onSetB(t_polystep *x, t_floatarg f){
    //New number for B of A:B
    polystep_setMods(x, x->mod_A, f);
}

//The _new method is a class constructor
//It is required to be named [filename]_new()
void *polystep_new(t_floatarg f1, t_floatarg f2){
    //Create an instance of the polystep class
    t_polystep *x = (t_polystep *)pd_new(polystep_class);
    
    //Initialize the counts
    //Since we'll be doing this in a few different locations, we'll create a method to accomplish this
    polystep_resetCount(x);
    
    //Initialize the mods (e.g. num % mod_A)
    //Since we'll be doing this in a few different locations, we'll create a method to accomplish this
    polystep_setMods(x, f1, f2);

    //Create inlets
    //The left-most inlet is created and destroyed automatically
    //Any additional inlets needed must be explicilty created
    //Inlets are created from left to right on the object
    //Handles (pointers, really) are stored so that we can free them later
    x->in_mod_A = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("ratio_A"));
    x->in_mod_B = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("ratio_B"));

    //Create outlets
    //Unlike the first inlet, the first isn' created automatically
    //Any outlets needed must be explicitly created
    //Outlets are created from left to right on the object
    //Handles (pointers, really) are stored so that we can send data to the outlets and/or free them later
    x->out_A = outlet_new(&x->x_obj, &s_bang);
    x->out_B = outlet_new(&x->x_obj, &s_bang);
    x->out_synch = outlet_new(&x->x_obj, &s_bang);
    x->out_count = outlet_new(&x->x_obj, &s_float);
      
    //Return the instance
    return (void *)x;
}

void polystep_free(t_polystep *x){
    //If we create any inlets or outlets ourselves, we need to free them to avoid memory leaks
    inlet_free(x->in_mod_A);
    inlet_free(x->in_mod_B);
    outlet_free(x->out_A);
    outlet_free(x->out_B);
    outlet_free(x->out_synch);
    outlet_free(x->out_count);
}

//The _setup method initializes the class in memory
//This method is the place where class behaviors are added
//It is required to be named [filename]_setup()
void polystep_setup(void){
    //Initialize the class
    polystep_class = class_new(gensym("polystep"),
                               (t_newmethod)polystep_new,
                               (t_method)polystep_free,
                               sizeof(t_polystep),
                               CLASS_DEFAULT,
                               A_DEFFLOAT, //A of A:B
                               A_DEFFLOAT, //B of A:B
                               0);
    //Define the handling of various inputs
    
    //Bang
    class_addbang(polystep_class, (t_method)polystep_onBangMsg);

    //List: set the ratio and reset
    class_addlist(polystep_class, (t_method)polystep_onListMsg);
    
    //Reset: start counting at 0 again
    class_addmethod(polystep_class,
                    (t_method)polystep_onResetMsg,
                    gensym("reset"),
                    0);

    //ratio_A: set A but don't reset
    class_addmethod(polystep_class,
                    (t_method)polystep_onSet_A,
                    gensym("ratio_A"),
                    A_DEFFLOAT, //A of A:B
                    0);
    
    //ratio_B: set B but don't reset
    class_addmethod(polystep_class,
                    (t_method)polystep_onSetB,
                    gensym("ratio_B"),
                    A_DEFFLOAT, //B of A:B
                    0);
}
