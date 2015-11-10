#include "interface.h"
#include "nucleo.h"

//****************************************************************************
//*********************** CALLBACK DOS BOTOES DO FORMULARIO *******************
//****************************************************************************
int callback_carregar_sint_chamada=0;
int arquivo_escolhido = 0;

void prgs_callback(FL_OBJECT *obj, long user_data) {
    fdui = obj->form->fdui;
    callback_carregar_sint_chamada=1;
    //const char *fname;
    if ( ( fname = fl_show_file_selector( "File To Load", "", "", "" ) ) )
    {
        if ( ! fl_load_browser( fdui->dados_programas, fname ) )
            fl_add_browser_line( fdui->dados_programas,"NO SUCH FILE!" );
        else
            fl_add_browser_line( fdui->acontecimentos,  "Programa Carregado");
            arquivo_escolhido=1;

    }

}

void sorteio_callback(FL_OBJECT *obj, long user_data) {
    FD_projeto *fdui = obj->form->fdui;
    char num[100];
    sprintf(num, "O numero sorteado foi: %d", interruptControl());
    fl_add_browser_line( fdui->acontecimentos, num );
}

void limpar_callback(FL_OBJECT *obj, long user_data) {
    FD_projeto *fdui = obj->form->fdui;
    fl_clear_browser(fdui->acontecimentos);
}

void cria_processo_callback(FL_OBJECT *obj, long user_data) {
    FD_projeto *fdui = obj->form->fdui;
    fl_add_browser_line( fdui->acontecimentos, "Funcao ainda nao implementada" );
    cria_processos_chamada = 1;
}


//****************************************************************************
//******************************** FORMULARIO ********************************
//****************************************************************************

FD_projeto *create_form_projeto(void)
{
    FL_OBJECT *obj;
    fdui = ( FD_projeto * ) fl_malloc( sizeof *fdui );

    fdui->vdata = fdui->cdata = NULL;
    fdui->ldata = 0;

    fdui->projeto = fl_bgn_form( FL_NO_BOX, 600, 400 );

    obj = fl_add_box( FL_FLAT_BOX, 0, 0, 600, 400, "" );

    fdui->dados_programas = obj = fl_add_browser( FL_NORMAL_BROWSER, 20, 210, 200, 150, "" );

    fdui->acontecimentos = obj = fl_add_browser( FL_NORMAL_BROWSER, 20, 20, 200, 150, "" );

    fdui->carregar = obj = fl_add_button( FL_NORMAL_BUTTON, 5, 180, 110, 20, "Carregar Programa" );
    fl_set_object_callback(obj, prgs_callback, 0);

    fdui->executar = obj = fl_add_button( FL_NORMAL_BUTTON, 60, 370, 120, 20, "Criar Processo" );
    fl_set_object_callback(obj, cria_processo_callback, 0);

    fdui->log = obj = fl_add_browser( FL_NORMAL_BROWSER, 250, 10, 320, 350, "" );

    obj = fl_add_button( FL_NORMAL_BUTTON, 120, 180, 60, 20, "Sorteio" );
    fl_set_object_callback(obj, sorteio_callback, 0);

    obj = fl_add_button( FL_NORMAL_BUTTON, 185, 180, 60, 20, "Limpar" );
    fl_set_object_callback(obj, limpar_callback, 0);

    fl_end_form( );

    fdui->projeto->fdui = fdui;

    return fdui;
}
