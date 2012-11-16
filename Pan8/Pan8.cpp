//-----------------------------------------------------------------------------
// Entaro ChucK Developer!
// This is a Chugin boilerplate, generated by chugerate!
//-----------------------------------------------------------------------------

// this should align with the correct versions of these ChucK files
#include "chuck_dl.h"
#include "chuck_def.h"

// general includes
#include <stdio.h>
#include <limits.h>
#include <math.h>

// declaration of chugin constructor
CK_DLL_CTOR(pan8_ctor);
// declaration of chugin desctructor
CK_DLL_DTOR(pan8_dtor);

// example of getter/setter
CK_DLL_MFUN(pan8_setPan);
CK_DLL_MFUN(pan8_getPan);

// for Chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICKF(pan8_tickf);

// this is a special offset reserved for Chugin internal data
t_CKINT pan8_data_offset = 0;


// class definition for internal Chugin data
// (note: this isn't strictly necessary, but serves as example
// of one recommended approach)
class Pan8
{
public:
    // constructor
    Pan8( t_CKFLOAT fs)
    {
        m_pan = 0.5;
    }

    // for Chugins extending UGen
    void tick( SAMPLE * in, SAMPLE * out, int nframes )
    {
        int c = ((int)floorf(m_pan))%8;
        int c_1 = ((int)ceilf(m_pan))%8;
        float mod = m_pan - floorf(m_pan);
        
        float g = cosf(M_PI/2*mod);
        float g_1 = sinf(M_PI/2*mod);
        
        memset(out, 0, sizeof(SAMPLE)*8*nframes);
        
        for(int i = 0; i < nframes; i++)
        {
            out[i*8+c] = g * in[i*8];
            out[i*8+c_1] = g_1 * in[i*8];
        }
    }

    // set parameter example
    float setPan( t_CKFLOAT p )
    {
        m_pan = p;
        return p;
    }

    // get parameter example
    float getPan() { return m_pan; }
    
private:
    // instance data
    float m_pan;
};


// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( Pan8 )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "Pan8");
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "Pan8", "UGen");

    // register the constructor (probably no need to change)
    QUERY->add_ctor(QUERY, pan8_ctor);
    // register the destructor (probably no need to change)
    QUERY->add_dtor(QUERY, pan8_dtor);
    
    // for UGen's only: add tick function
    QUERY->add_ugen_funcf(QUERY, pan8_tickf, NULL, 8, 8);
    
    // NOTE: if this is to be a UGen with more than 1 channel, 
    // e.g., a multichannel UGen -- will need to use add_ugen_funcf()
    // and declare a tickf function using CK_DLL_TICKF

//    // example of adding setter method
//    QUERY->add_mfun(QUERY, pan8_setAngle, "float", "angle");
//    // example of adding argument to the above method
//    QUERY->add_arg(QUERY, "float", "arg");
//    
//    // example of adding getter method
//    QUERY->add_mfun(QUERY, pan8_getAngle, "float", "angle");
    
    // example of adding setter method
    QUERY->add_mfun(QUERY, pan8_setPan, "float", "pan");
    // example of adding argument to the above method
    QUERY->add_arg(QUERY, "float", "arg");
    
    // example of adding getter method
    QUERY->add_mfun(QUERY, pan8_getPan, "float", "pan");
    
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    pan8_data_offset = QUERY->add_mvar(QUERY, "int", "@p8_data", false);

    // end the class definition
    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);

    // wasn't that a breeze?
    return TRUE;
}


// implementation for the constructor
CK_DLL_CTOR(pan8_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, pan8_data_offset) = 0;
    
    // instantiate our internal c++ class representation
    Pan8 * bcdata = new Pan8(API->vm->get_srate());
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, pan8_data_offset) = (t_CKINT) bcdata;
}


// implementation for the destructor
CK_DLL_DTOR(pan8_dtor)
{
    // get our c++ class pointer
    Pan8 * bcdata = (Pan8 *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
    // check it
    if( bcdata )
    {
        // clean up
        delete bcdata;
        OBJ_MEMBER_INT(SELF, pan8_data_offset) = 0;
        bcdata = NULL;
    }
}


// implementation for tick function
CK_DLL_TICKF(pan8_tickf)
{
    // get our c++ class pointer
    Pan8 * c = (Pan8 *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
 
    if(c) c->tick(in, out, nframes);

    // yes
    return TRUE;
}


// example implementation for setter
CK_DLL_MFUN(pan8_setPan)
{
    // get our c++ class pointer
    Pan8 * bcdata = (Pan8 *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
    // set the return value
    RETURN->v_float = bcdata->setPan(GET_NEXT_FLOAT(ARGS));
}


// example implementation for getter
CK_DLL_MFUN(pan8_getPan)
{
    // get our c++ class pointer
    Pan8 * bcdata = (Pan8 *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
    // set the return value
    RETURN->v_float = bcdata->getPan();
}
