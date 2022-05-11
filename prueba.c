

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

typedef struct def_Doctor
{
  char nombre[50];
  char especialidad1[50];
  char especialidad2[50];
  char estado[20];
  int telefono_urge;
  char direccion[50];
  int telefono;
  int consultorio;
  char dias[20];
  char horario [10];
  struct def_Doctor *sig;
}TipoDoctor;

typedef struct def_Paciente
{
  char nombre[50];
  char direccion[50];
  int telefono;
  char sexo;
  char fecha[10];
  int edad;
  float estatura;
  char alergias[50];
  char sangre[5];
  char padecimientos[50];
  struct def_Paciente *sig;
  struct def_Historia *his;
}TipoPaciente;

typedef struct def_Historia
{
  char nombre_p[50];
  char nombre_d[50];
  char fecha[15];
  char diagnostico[60];
  char tratamiento[60];
  char anotaciones[50];
  int numero;
  struct def_Historia *sig;
}TipoHistoria;


typedef struct {
  GtkWidget *widget;
  gint index;
  const gchar *title;
  GtkAssistantPageType type;
  gboolean complete;
} PageInfo;


typedef struct def_widget
{

  GtkWidget* lista1[15];
  TipoPaciente *Pac01;
  TipoDoctor *Doc01;
  TipoHistoria *His;

}TipoLista;

enum{
  NOMBRE=0,
  ESP_1,
  ESP_2,
  ESTADO,
  TEL_URG,
  DIRECCION,
  TEL,
  CONSULTORIO,
  DIAS,
  HORARIO,
  COLUM
};

enum{
  NOMBREP=0,
  DIRECCIONP,
  TELEFONOP,
  SEXOP,
  FECHAP,
  EDADP,
  ESTATURAP,
  ALERGIAP,
  SANGREP,
  PADECIMIENTOSP,
  COLUMP
};
/**
*Es importante mencionar que en cada una de nuestras funciones se les debera pasar como parametro
*un apuntador a una esructura TipoLista ya que esta contiene un arreglo de GtkWidgets con los que
*podremos interactuar desde cualquier otra funcion. Ademas de que contiene los apuntadores a los
*incicios de las listas dinamicas de pacientes y doctores.
*/

void assistant_cancel (GtkAssistant*, gpointer);
void assistant_close (GtkAssistant*, gpointer);
void alta_Doc(GtkWidget *menu, gpointer lista);
void consult_Doc(GtkWidget *menu, gpointer lista);
void ayuda();
void Mod_Doc1(GtkWidget *menu, gpointer lista);
void Busca_D(GtkWidget *menu, gpointer lista);
void Mod_Doc(GtkWidget *menu, gpointer lista);
void Editar_Doc(GtkWidget *menu, gpointer lista);
void Cambiar_D(GtkWidget *menu, gpointer lista);
void Mod_Pac(GtkWidget *menu, gpointer lista);
void Busca_P(GtkWidget *menu, gpointer lista);
void Cambiar_P(GtkWidget *menu, gpointer lista);
gboolean button_press_event (GtkWidget *eventbox, GdkEventButton *event, GtkWidget *menu);
void menu(TipoPaciente **Pac0, TipoDoctor **Doc0);
void StopTheApp(GtkWidget *window, gpointer data);
void alta_Pac(GtkWidget *menu, gpointer lista);
void consult_Pac(GtkWidget *menu, gpointer lista);

void alta_His();
void consult_His(GtkWidget *nom,  gpointer lista);
void Mod_His();
int acerca();
void cargar(TipoPaciente **Pac0, TipoDoctor **Doc0);
void Agrega(GtkWidget *nom,  gpointer lista);
void Destroy(GtkWidget *window, gpointer data);
void Agrega_D(GtkWidget *nom,  gpointer lista);
void timestamp(char fecha[20]);
void Agrega_H(GtkWidget *nom,  gpointer lista);
void plasma(TipoLista *datos);
void Todas_H(GtkWidget *menu, gpointer lista);
void Desplegar_His(GtkWidget *menu, gpointer lista);
void Avanza_H(GtkWidget *menu, gpointer lista);
void Busca_H(GtkWidget *menu, gpointer lista);
void switchp(GtkButton *,GtkNotebook *);
void steup_tree_v(GtkWidget* treeview);
void switchp_p(GtkButton *,GtkNotebook *);
void steup_tree_v_p(GtkWidget* treeview);
void busca1(GtkWidget *,gpointer lista);
void busca2(GtkWidget *,gpointer lista);
void buscap(GtkWidget *,gpointer lista);

void Editar_His(GtkWidget *menu, gpointer lista);
void Cambiar_H(GtkWidget *menu, gpointer lista);

gint main ( gint argc, gchar *argv[])
{
  TipoPaciente *Pac0=NULL;
  TipoDoctor *Doc0=NULL;

  gtk_init(&argc, &argv);
  cargar(&Pac0, &Doc0);
  menu(&Pac0, &Doc0);

  gtk_main();

  return 0;



}
/**
 *Dentro de esta funcion se elabora la parte gráfica del menu principal del programa
 *Es una interfaz sencilla siendo solo 4 pestañas las que contienen los submenus de
 *Pacientes, Doctores, Historias clínicas e informacion del sistema
 *Cada uno de los submenus tiene una señal conectada a funciones diferentes.
 *
 *@author Mirna Cardona
 */
void menu(TipoPaciente **Pac0, TipoDoctor **Doc0)
{ GtkWidget *window;

  GtkWidget *alt, *cons, *mod, *Doc, *Pac, *Hist, *separator;
  GtkWidget *box, *menubar, *Docmenu, *Pacmenu, *Histmenu, *Acer, *Acermenu, *Cred, *Info, *Doc2menu, *Esp, *Esp1, *Esp2;
  GtkWidget *verticalbox, *image, *image2;
  TipoLista* lista;
  GdkPixbuf *logo, *hosp;
    GError *error = NULL;
  lista=(TipoLista*)malloc(sizeof(TipoLista));


  lista->Doc01=*Doc0;
  lista->Pac01=*Pac0;

window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  box = gtk_hbox_new(FALSE,0);
  verticalbox=gtk_vbox_new(FALSE, 0);

  logo = gdk_pixbuf_new_from_file ("/home/ic18mcn/ProgAp/Lab/Proyecto/logo.jpg", &error);
  hosp  = gdk_pixbuf_new_from_file ("/home/ic18mcn/ProgAp/Lab/Proyecto/hosp.png", &error);
  image= gtk_image_new_from_pixbuf (logo);
  image2=gtk_image_new_from_pixbuf (hosp);
 menubar = gtk_menu_bar_new ();
//se crean las pestañas principales de nuestro menu
 Doc = gtk_menu_item_new_with_label ("Doctores");
 Pac = gtk_menu_item_new_with_label ("Pacientes");
 Hist = gtk_menu_item_new_with_label ("Historia Clìnica");
 Acer = gtk_menu_item_new_with_label ("Acerca de ...");

 Docmenu = gtk_menu_new ();
 Doc2menu=gtk_menu_new();
 Pacmenu = gtk_menu_new ();
 Histmenu = gtk_menu_new ();
  Acermenu=gtk_menu_new();

 gtk_menu_item_set_submenu (GTK_MENU_ITEM (Doc), Docmenu);
 gtk_menu_item_set_submenu (GTK_MENU_ITEM (Pac), Pacmenu);
 gtk_menu_item_set_submenu (GTK_MENU_ITEM (Hist), Histmenu);
 gtk_menu_item_set_submenu (GTK_MENU_ITEM (Acer), Acermenu);


 gtk_menu_shell_append (GTK_MENU_SHELL (menubar), Doc);
 gtk_menu_shell_append (GTK_MENU_SHELL (menubar), Pac);
 gtk_menu_shell_append (GTK_MENU_SHELL (menubar), Hist);
 gtk_menu_shell_append (GTK_MENU_SHELL (menubar), Acer);
 ////////////////////////////////////////////////////////
 //MENU DE ACERCA DE...

 Cred = gtk_menu_item_new_with_label ("Informacion del sistema");
 Info = gtk_menu_item_new_with_label("Ayuda");

 g_signal_connect (G_OBJECT (Cred), "activate", G_CALLBACK (acerca), NULL);
 g_signal_connect (G_OBJECT (Info), "activate", G_CALLBACK (ayuda), NULL);//funcion

  gtk_menu_shell_append (GTK_MENU_SHELL (Acermenu), Cred);
 gtk_menu_shell_append (GTK_MENU_SHELL (Acermenu), Info);

 ///////////////////////////////////////
 //MENU DE DOCTORES
 alt = gtk_menu_item_new_with_label ("Altas");
 cons = gtk_menu_item_new_with_label("Consulta");
 mod =gtk_menu_item_new_with_label("Modificaciones");
 separator = gtk_separator_menu_item_new ();

 g_signal_connect (G_OBJECT (mod), "activate", G_CALLBACK (Mod_Doc1), lista);
 g_signal_connect (G_OBJECT (cons), "activate", G_CALLBACK (consult_Doc), lista);
 gtk_menu_shell_append (GTK_MENU_SHELL (Docmenu), alt);
 gtk_menu_shell_append (GTK_MENU_SHELL (Docmenu), cons);
 gtk_menu_shell_append (GTK_MENU_SHELL (Docmenu), mod);

 g_signal_connect (G_OBJECT (alt), "activate", G_CALLBACK (alta_Doc), lista);
 //g_signal_connect (G_OBJECT (mod), "activate", G_CALLBACK (Mod_Doc1), lista);

 ////////////////////////////
 //MENU DE PACIENTES

  alt = gtk_menu_item_new_with_label ("Altas");
 cons = gtk_menu_item_new_with_label("Consulta");
 mod =gtk_menu_item_new_with_label("Modificaciones");
 separator = gtk_separator_menu_item_new ();


 gtk_menu_shell_append (GTK_MENU_SHELL (Pacmenu), alt);
 gtk_menu_shell_append (GTK_MENU_SHELL (Pacmenu), cons);
 gtk_menu_shell_append (GTK_MENU_SHELL (Pacmenu), mod);

 g_signal_connect (G_OBJECT (alt), "activate", G_CALLBACK (alta_Pac), lista);
 g_signal_connect (G_OBJECT (cons), "activate", G_CALLBACK (consult_Pac), lista);
 g_signal_connect (G_OBJECT (mod), "activate", G_CALLBACK (Mod_Pac), lista);

 //////////////////////////////////////////////////
 //MENU DE HISTORIA CLÌNICA
 alt = gtk_menu_item_new_with_label ("Altas");
 cons = gtk_menu_item_new_with_label("Consulta");
 mod =gtk_menu_item_new_with_label("Modificaciones");
 separator = gtk_separator_menu_item_new ();


Doc2menu=gtk_menu_new();

 Esp = gtk_menu_item_new_with_label ("Consulta una ficha");
 Esp1 = gtk_menu_item_new_with_label ("Desplegar historia de un paciente");


 gtk_menu_shell_append (GTK_MENU_SHELL (Doc2menu), Esp);
 gtk_menu_shell_append (GTK_MENU_SHELL (Doc2menu), Esp1);

 gtk_menu_item_set_submenu (GTK_MENU_ITEM (cons), Doc2menu);


 g_signal_connect (G_OBJECT (alt), "activate", G_CALLBACK (alta_His), lista);

 g_signal_connect (G_OBJECT (mod), "activate", G_CALLBACK (Mod_His), lista);


  g_signal_connect (G_OBJECT (Esp1), "activate", G_CALLBACK (Desplegar_His), lista);
 g_signal_connect (G_OBJECT (Esp), "activate", G_CALLBACK (consult_His), lista);


 gtk_menu_shell_append (GTK_MENU_SHELL (Histmenu), alt);
 gtk_menu_shell_append (GTK_MENU_SHELL (Histmenu), cons);
 gtk_menu_shell_append (GTK_MENU_SHELL (Histmenu), mod);

 ////////////////////////////////////////////////////
 gtk_box_pack_start(GTK_BOX(verticalbox), image, FALSE, FALSE, 20);
 gtk_box_pack_start(GTK_BOX(box), menubar ,FALSE,FALSE, 0);

 gtk_box_pack_start(GTK_BOX(verticalbox), box,FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(verticalbox), image2, FALSE, FALSE, 0);
  /*box=gtk_hbox_new(TRUE, 10);
    gtk_box_pack_start(GTK_BOX(verticalbox), box, FALSE, FALSE, 0);*/

 gtk_container_add (GTK_CONTAINER (window), verticalbox);

 gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),lista);
  gtk_widget_show_all (window);
}
void StopTheApp(GtkWidget *window, gpointer data)
{
  TipoLista* datos= (TipoLista*)data;
  plasma(datos);
  gtk_main_quit();
}
/**
 *Dentro de esta funcion se elabora la parte grafica del submenu Dar alta de Doctores
 *Una vez creada la interfaz gráfica se crea un boton el cual cuando el usuario lo selecione
 *Se insertara en la lista dinamica el nuevo doctor.
 *
 *
 *@author Mirna Cardona
 */
void alta_Doc(GtkWidget *menu, gpointer lista)
{GtkWidget *window, *nom, *box, *box1,  *vbox,*label, *vbox1, *vbox2;
TipoLista* datos= (TipoLista*)lista;


window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (window), "Alta de Doctores");
gtk_container_set_border_width (GTK_CONTAINER (window), 10);

label = gtk_label_new ("Datos del Doctor:");

vbox = gtk_vbox_new (FALSE, 5);
gtk_box_pack_start_defaults (GTK_BOX (vbox), label);


label = gtk_label_new ("Nombre:");
nom = gtk_entry_new ();
datos->lista1[0] = nom;
gtk_entry_set_visibility (GTK_ENTRY (nom), TRUE);

box=gtk_vbox_new(FALSE, 5);

vbox1 = gtk_hbox_new (FALSE, 5);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[0]);
gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

vbox1 = gtk_hbox_new (FALSE, 5);

label = gtk_label_new ("Dirección:");
datos->lista1[1] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[1]), TRUE);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[1]);
gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

label = gtk_label_new ("Teléfono de urgencias:");
datos->lista1[2] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[2]), TRUE);


vbox1 = gtk_hbox_new (FALSE, 5);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[2]);
gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

label = gtk_label_new ("Especialidad 1:");
datos->lista1[3] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[3]), TRUE);


vbox1 = gtk_hbox_new (FALSE, 5);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[3]);
gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


label = gtk_label_new ("Especialidad 2:");
datos->lista1[4] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[4]), TRUE);


vbox1 = gtk_hbox_new (FALSE, 5);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[4]);
gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


vbox2 = gtk_vbox_new (FALSE, 5);

label = gtk_label_new ("Estatus:");
datos->lista1[5] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[5]), TRUE);


vbox1=gtk_hbox_new(TRUE,5);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[5]);
gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

label = gtk_label_new ("Telefono:");
datos->lista1[6] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[6]), TRUE);


vbox1=gtk_hbox_new(FALSE,5);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[6]);
gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

label = gtk_label_new ("Dias de consulta:");
datos->lista1[7] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[7]), TRUE);


vbox1=gtk_hbox_new(FALSE,5);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[7]);

label = gtk_label_new ("Horiario:");

 datos->lista1[8] = gtk_entry_new();
gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[8]);


gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);
label = gtk_label_new ("Consultorio:");
datos->lista1[9] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[9]), TRUE);


vbox1=gtk_hbox_new(FALSE,5);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[9]);

gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);


datos->lista1[10]=window;
//Se le asigna al boton la funcion de Agrega_D

nom= gtk_button_new_with_label("Aceptar");
gtk_box_pack_start(GTK_BOX(vbox2),nom,FALSE,TRUE,0);
gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Agrega_D),datos);
gtk_widget_show(nom);

box1=gtk_hbox_new(TRUE,5);
gtk_box_pack_start_defaults (GTK_BOX (box1), box);
gtk_box_pack_start_defaults (GTK_BOX (box1), vbox2);

gtk_box_pack_start_defaults (GTK_BOX (vbox), box1);

gtk_container_add (GTK_CONTAINER (window), vbox);

gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
gtk_widget_show_all (window);
}
/**
*consul_Doc
*
*Esta función crea una ventana que contenga un notebook donde se mostrará, tres opciones para consultar los doctores
*el primero mostrará la treeview con todos los doctores, en la segunda aparecerá una entri box, un label y un botón para buscar
*las especialidades de los doctores, donde se creará una ventana con cun un filtro de las especialidades,se enviará la lista a una función, en caso de no encontrar nada o no introducir nada se le notificará al usuario,
*el tercero es parecido al segundo solo que este buscara por nombre
*
*@Autor: Enrique Guevara
*
*/

void consult_Doc(GtkWidget *menu, gpointer lista)
{

  GtkWidget *window,*notebook, *treeview,*scrolled_win, *box, *viewport,*hbox1,*hbox2,*vbox3,*vbox4,*dialog;
  GtkWidget *label,*label1,*label2,*label3,*cbox,*cbox1,*button,*button1;
  GtkListStore *store;
  GtkTreeIter iter;
  GtkAdjustment *horizontal, *vertical;
  TipoDoctor *temp;
  TipoLista* datos= (TipoLista*)lista;
  char nomre[50], espa1[50],espa2[50];
  int i=0;

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request(window,850,500);
  gtk_window_set_title(GTK_WINDOW(window),"Doctores");


  box = gtk_vbox_new(TRUE,5);
  hbox2 = gtk_hbox_new(TRUE,5);
  hbox1 = gtk_hbox_new(TRUE,5);
  vbox3=gtk_vbox_new(TRUE,5);
  vbox4=gtk_vbox_new(TRUE,5);
  if(datos->Doc01!=NULL){
    temp=datos->Doc01;

    treeview=gtk_tree_view_new();
    steup_tree_v(treeview);
    store=gtk_list_store_new(COLUM,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT);
    while(temp!=NULL)
      {
	strcpy(nomre,temp->nombre);
	strcpy(espa1,temp->especialidad1);
	strcpy(espa2,temp->especialidad2);

	for(i=0;i<=strlen(nomre)-1;i++){
	  if(nomre[i]>='a' && nomre[i]<='z'){
	    nomre[i]=nomre[i]-'a'+'A';
	  }
	}

	for(i=0;i<=strlen(temp->especialidad1)-1;i++){
	  if(espa1[i]>='a' && espa1[i]<='z'){
	    espa1[i]=espa1[i]-'a'+'A';
	  }
	}

	for(i=0;i<=strlen(temp->especialidad2)-1;i++){
	  if(espa2[i]>='a' && espa2[i]<='z'){
	    espa2[i]=espa2[i]-'a'+'A';
	  }
	}

	gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,NOMBRE,nomre,ESP_1,espa1,ESP_2,espa2,ESTADO,temp->estado,TEL_URG,temp->telefono_urge,DIRECCION,temp->direccion,TEL,temp->telefono,CONSULTORIO,temp->consultorio,DIAS,temp->dias,HORARIO,temp->horario,-1);
	temp=temp->sig;
      }
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(store));
    g_object_unref(store);
    scrolled_win=gtk_scrolled_window_new(NULL,NULL);
    horizontal = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (scrolled_win));
    vertical = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (scrolled_win));
    viewport = gtk_viewport_new (horizontal, vertical);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(viewport),treeview);
    gtk_box_pack_start(GTK_BOX(box),viewport,FALSE,FALSE,0);
    //Fin de note 1
    //Inicio de note 2
    label=gtk_label_new("Especialidad");
    cbox= gtk_entry_new();
    datos->lista1[0] = cbox;
    datos->lista1[1] = hbox2;
    button1=gtk_button_new_with_label("Busca");
    gtk_box_pack_start(GTK_BOX(hbox1),label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox1),cbox,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox1),button1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox3),hbox1,FALSE,FALSE,0);
    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(busca1),datos);

    //Fin de note 2
    //Inicio del note3
    label=gtk_label_new("Nombre");
    cbox1= gtk_entry_new();
    datos->lista1[2] = cbox1;
    button=gtk_button_new_with_label("Busca");
    gtk_box_pack_start(GTK_BOX(hbox2),label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox2),cbox1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox2),button,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox4),hbox2,FALSE,FALSE,0);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(busca2),datos);

    //Fin del note 3

    notebook=gtk_notebook_new();
    label1=gtk_label_new("Global");
    label2=gtk_label_new("Especialidad");
    label3=gtk_label_new("Nombre");

    g_signal_connect(GTK_WIDGET(label1),"clicked",G_CALLBACK(switchp),(gpointer) notebook);
    g_signal_connect(GTK_WIDGET(label2),"clicked",G_CALLBACK(switchp),(gpointer) notebook);
    g_signal_connect(G_OBJECT(label3),"clicked",G_CALLBACK(switchp),(gpointer) notebook);


    gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),box,label1);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),vbox3,label2);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),vbox4,label3);

    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_BOTTOM);

    gtk_container_add(GTK_CONTAINER(window),notebook);
    gtk_widget_show_all(window);
  }else{
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "No hay doctores aun");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_signal_connect(GTK_OBJECT(dialog),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
  }

}

/**
 *Dentro de esta funcion se elabora la parte grafica del submenu Dar alta de Pacientes
 *Una vez creada la interfaz gráfica se crea un boton el cual cuando el usuario lo selecione
 *Se insertara en la lista dinamica el nuevo paciente.
 *
 *
 */
void alta_Pac(GtkWidget *menu, gpointer lista)
{
  GtkWidget *window, *nom, *box, *box1,  *vbox, *label, *vbox1, *vbox2, *spin_float;
  GtkAdjustment *float_pt;
  TipoLista* datos= (TipoLista*)lista;


  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Alta de Pacientes?");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  label = gtk_label_new ("Datos del Paciente:");

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_box_pack_start_defaults (GTK_BOX (vbox), label);

  label = gtk_label_new ("Nombre:");
  nom = gtk_entry_new ();
  datos->lista1[0] = nom;
  gtk_entry_set_visibility (GTK_ENTRY (nom), TRUE);

  box=gtk_vbox_new(FALSE, 5);

  vbox1 = gtk_hbox_new (FALSE, 5);
  gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[0]);
  gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

  vbox1 = gtk_hbox_new (FALSE, 5);

  label = gtk_label_new ("Dirección:");
  datos->lista1[1] = gtk_entry_new ();
  gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[1]), TRUE);

  gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[1]);
  gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

  label = gtk_label_new ("Teléfono:");
  datos->lista1[2] = gtk_entry_new ();
  gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[2]), TRUE);

  vbox1 = gtk_hbox_new (FALSE, 5);

  gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[2]);
  gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

 label = gtk_label_new ("Alergias:");
datos->lista1[3] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[3]), TRUE);

vbox1 = gtk_hbox_new (FALSE, 5);

 gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
 gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[3]);
 gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


 label = gtk_label_new ("Padecimientos crónicos:");
datos->lista1[4] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[4]), TRUE);

 vbox1 = gtk_hbox_new (FALSE, 5);

 gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
 gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[4]);
 gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


vbox2 = gtk_vbox_new (FALSE, 5);

label = gtk_label_new ("Sexo:");
datos->lista1[5] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[5]), TRUE);

vbox1=gtk_hbox_new(TRUE,5);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
 gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[5]);
 gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

 label = gtk_label_new ("Fecha de nacimiento:");
datos->lista1[6] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[6]), TRUE);

vbox1=gtk_hbox_new(FALSE,5);

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
 gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[6]);
 gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

label = gtk_label_new ("Edad:");
datos->lista1[7] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[7]), TRUE);

vbox1=gtk_hbox_new(FALSE,5);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
 gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[7]);

 label = gtk_label_new ("Estatura:");

 float_pt = GTK_ADJUSTMENT (gtk_adjustment_new (0.5, 0.0, 2.0, 0.01, 0.5, 0));
 datos->lista1[8] = gtk_spin_button_new (float_pt, 0.01, 2);
///////como sacar el valor del spin

gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[8]);

 gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

label = gtk_label_new ("Sangre:");
datos->lista1[9] = gtk_entry_new ();
gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[9]), TRUE);


vbox1=gtk_hbox_new(FALSE,5);
gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
 gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[9]);

gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);


datos->lista1[10]=window;

  nom= gtk_button_new_with_label("Aceptar");
  gtk_box_pack_start(GTK_BOX(vbox2),nom,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Agrega),datos);
  gtk_widget_show(nom);

box1=gtk_hbox_new(TRUE,5);
gtk_box_pack_start_defaults (GTK_BOX (box1), box);
gtk_box_pack_start_defaults (GTK_BOX (box1), vbox2);

gtk_box_pack_start_defaults (GTK_BOX (vbox), box1);

gtk_container_add (GTK_CONTAINER (window), vbox);

gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
 gtk_widget_show_all (window);

}

/**
*Dentro de esta funcion se elabora la parte grafica del submenu Dar alta de Historias clínicas
 *Una vez creada la interfaz gráfica se crea un boton el cual cuando el usuario lo selecione
 *Se insertara en la lista dinamica la nueva historia.
 *
 *
 */
void alta_His(GtkWidget *menu, gpointer lista)
{GtkWidget *box, *vbox, *nom;
  GtkWidget *label,*window;
  char fecha[20];
   TipoLista* datos= (TipoLista*)lista;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Alta de Historias");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  label = gtk_label_new ("Datos de la cita:");

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_box_pack_start_defaults (GTK_BOX (vbox), label);

  box = gtk_hbox_new(FALSE,5);
  label = gtk_label_new ("Nombre del Doctor:");
  datos->lista1[0]= gtk_entry_new ();
  gtk_box_pack_start_defaults (GTK_BOX (box), label);
  gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[0]);


  label = gtk_label_new ("Nombre del Paciente:");
  datos->lista1[1]= gtk_entry_new ();
  gtk_box_pack_start_defaults (GTK_BOX (box), label);
  gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[1]);

  gtk_box_pack_start_defaults (GTK_BOX (vbox), box);
  box = gtk_hbox_new(FALSE,5);

  timestamp(fecha);


  label = gtk_label_new ("Fecha de la cita:");
  gtk_box_pack_start_defaults (GTK_BOX (box), label);
  datos->lista1[2] = gtk_label_new (fecha);
  gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[2]);

  gtk_box_pack_start_defaults (GTK_BOX (vbox), box);

  box = gtk_hbox_new(TRUE,5);
  label = gtk_label_new ("Diagnostico:");
  datos->lista1[3] = gtk_entry_new ();
  gtk_box_pack_start_defaults (GTK_BOX (box), label);
  gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[3]);

  label = gtk_label_new ("Tratamiento:");
  datos->lista1[4] = gtk_entry_new ();
  gtk_box_pack_start_defaults (GTK_BOX (box), label);
  gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[4]);


  label = gtk_label_new ("Anotaciones:");
  datos->lista1[5] = gtk_entry_new ();
  gtk_box_pack_start_defaults (GTK_BOX (box), label);
  gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[5]);

  gtk_box_pack_start_defaults (GTK_BOX (vbox), box);

  datos->lista1[10]=window;

  nom= gtk_button_new_with_label("Aceptar");
  gtk_box_pack_start(GTK_BOX(vbox),nom,TRUE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Agrega_H),datos);
  gtk_widget_show(nom);


  gtk_container_add (GTK_CONTAINER (window), vbox);

  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
  gtk_widget_show_all (window);
}


/**
 *
 *Esta funcion elabora la parte grafica de la pestaña Acerca de.. donde se depliega la
 *información básica de nuestro programa como el nombre de los autores y las referencias
 *que se utilizaron. También se incluye el logo de nuestro programa que se llama logo.jpg
 *
 *@author Mirna Cardona
 */
int acerca()
{


GtkWidget *dialog;
 GdkPixbuf *logo;
 GError *error = NULL;

 const gchar *authors[] = {
 "Cardona Núñez Mirna Itzell Xochiquetzal ",
 "Gómez Álvarez Juan Pablo",
 "Carlos Enrique Guevara Gonzalez",

 NULL
 };
 const gchar *documenters[] = {
   "Andrew Krause. (2007). Foundations of GTK+ Development. NY: Apress.",
 NULL
 };
 dialog = gtk_about_dialog_new ();
 logo = gdk_pixbuf_new_from_file ("/home/ic18mcn/ProgAp/Lab/Proyecto/logo.jpg", &error);//ver la direccion del logo
 if (error == NULL)
 gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (dialog), logo);
 else
 {
 if (error->domain == GDK_PIXBUF_ERROR)
 g_print ("GdkPixbufError: %s\n", error->message);
 else
   if (error->domain == G_FILE_ERROR)
 	g_print ("GFileError: %s\n", error->message);
   else
 	g_print ("An error in the domain: %d has occurred!\n", error->domain);
 g_error_free (error);
 }
gtk_about_dialog_set_name (GTK_ABOUT_DIALOG (dialog), "MEDI+");
 gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (dialog), "1.0");
 gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (dialog), "(C) 2019 Programaciòn apicada");
 gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (dialog), "Todo de MEDI+");
 gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (dialog), authors);
 gtk_about_dialog_set_documenters (GTK_ABOUT_DIALOG (dialog), documenters);
  gtk_dialog_run (GTK_DIALOG (dialog));
 gtk_widget_destroy (dialog);
 return 0;
 //#AlanWasHere
}
/**
 *Esta función es de las más importantes de todas ya que es la que se encarga de leer los archivos
 *de pacientes, docotres e historias clínicas de cada uno de los pacientes.
 *Una vez que abre los archivos se encarga dentro de las listas dinámicas.
 *
 *
 *@author Mirna Cardona
 */
void cargar(TipoPaciente **Pac0, TipoDoctor **Doc0)
{FILE *archivo;
  TipoDoctor *temp, *temp2;
  TipoPaciente *temp3, *temp4;
  TipoHistoria *hist4, *estruc;

  archivo=fopen("doctores", "rt");
  temp=(TipoDoctor*)malloc(sizeof(TipoDoctor));                               	//Se le asigna un espacio de memoria a la variable temporal
//Para leer el archivo de Doctores

  if(archivo!=NULL)
	{while(fscanf(archivo, "Nombre: %s\n", temp->nombre)==1)
  {fscanf(archivo, "Especialidad 1: %s\n", temp->especialidad1);
	fscanf(archivo, "Especialidad 2: %s\n", temp->especialidad2);
	fscanf(archivo, "Estado: %s\n", temp->estado);
	fscanf(archivo, "Telefono de urgencias: %d\n", &temp->telefono_urge);
	fscanf(archivo, "Direccion: %s\n", temp->direccion);
	fscanf(archivo, "Telefono: %d\n", &temp->telefono);
	fscanf(archivo, "Consultorio: %d\n", &temp->consultorio);
	fscanf(archivo, "Dias: %s\n", temp->dias);
	fscanf(archivo, "Horario: %s\n" , temp->horario);


	temp->sig=NULL;

	if(*Doc0!=NULL)                                                             	//Si la lista no esta vacia entonces:
  	{temp2=*Doc0;                                                             	//Se le asigna la posición de la primera variable de la lista a una nueva variable temporal
    	while(temp2->sig!=NULL)                                                     	//Mientras que no se llegue al final de la lista
	temp2=temp2->sig;                                                               	//Se aumentará la posición de la variable temporal
    	temp2->sig=temp;                                                           	/*Si ya se llego al final entonces al apuntador del ultimo elemento de la lista se le
                                                                                  	asigna la variable a la que se le  cargo la información */
  	}else
  	*Doc0=temp;                                                               	//Si la lista está vacia entonces se le asignará a la primera posición la variable con los datos cargados.

	temp=(TipoDoctor*)malloc(sizeof(TipoDoctor));                               	//Se le asigna un espacio de memoria a la variable temporal

  }
  	fclose(archivo);
	}

  archivo=fopen("pacientes", "rt");
  temp3=(TipoPaciente*)malloc(sizeof(TipoPaciente));                               	//Se le asigna un espacio de memoria a la variable temporal

  //Para cargar el archivo de Pacientes
  if(archivo!=NULL)
	{while(fscanf(archivo, "Nombre: %s\n", temp3->nombre)==1)
  {fscanf(archivo, "Direccion: %s\n", temp3->direccion);
	fscanf(archivo, "Telefono: %d\n", &temp3->telefono);
	fscanf(archivo, "Sexo: %c\n", &temp3->sexo);
	fscanf(archivo, "Fecha: %s\n", temp3->fecha);
	fscanf(archivo, "Edad: %d\n", &temp3->edad);
	fscanf(archivo, "Estatura: %f\n", &temp3->estatura);
	fscanf(archivo, "Alergias: %s\n", temp3->alergias);
	fscanf(archivo, "Sangre: %s\n", temp3->sangre);
	fscanf(archivo, "Padecimientos: %s\n", temp3->padecimientos);
	temp3->his=NULL;


	temp3->sig=NULL;

	if(*Pac0!=NULL)                                                             	//Si la lista no esta vacia entonces:
  	{temp4=*Pac0;                                                             	//Se le asigna la posición de la primera variable de la lista a una nueva variable temporal
    	while(temp4->sig!=NULL)                                                     	//Mientras que no se llegue al final de la lista
	temp4=temp4->sig;                                                         	//Se aumentará la posición de la variable temporal
    	temp4->sig=temp3;                                                           	/*Si ya se llego al final entonces al apuntador del ultimo elemento de la lista se le
                    	asigna la variable a la que se le  cargo la información */
  	}else
  	*Pac0=temp3;                                                               	//Si la lista está vacia entonces se le asignará a la primera posición la variable con los datos cargados.

	temp3=(TipoPaciente*)malloc(sizeof(TipoPaciente));                               	//Se le asigna un espacio de memoria a la variable temporal

  }
  	fclose(archivo);
	}

  temp3=*Pac0;
  //Para abrir el archivo de las historias clinicas del paciente
  	while(temp3!=NULL)
  {

	archivo=fopen(temp3->nombre, "rt");
	//Se abrira el archivo de las historias clínicas de cada paciente
	if(archivo!=NULL)
  	{estruc=(TipoHistoria*)malloc(sizeof(TipoHistoria));
    	while(fscanf(archivo, "Nombre de paciente: %s\n", estruc->nombre_p)==1)
	{fscanf(archivo, "Nombre de Doctor: %s\n", estruc->nombre_d);
  	fscanf(archivo, "Fecha: %s\n", estruc->fecha);
  	fscanf(archivo, "Diagnostico: %s\n", estruc->diagnostico);
  	fscanf(archivo, "Tratamiento: %s\n", estruc->tratamiento);
  	fscanf(archivo, "Anotaciones: %s\n", estruc->anotaciones);
  	fscanf(archivo, "Numero de Ficha: %d\n",&estruc->numero);

  	estruc->sig=NULL;

  	if(temp3->his!=NULL)
    	{hist4=temp3->his;                                                             	//Se le asigna la posición de la primera variable de la lista a una nueva variable temporal
      	while(hist4->sig!=NULL)                                                     	//Mientras que no se llegue al final de la lista
  	hist4=hist4->sig;                                                         	//Se aumentará la posición de la variable temporal
      	hist4->sig=estruc;                                                           	/*Si ya se llego al final entonces al apuntador del ultimo elemento de la lista se le
                                                                                    	asigna la variable a la que se le  cargo la información */
    	}else

    	temp3->his=estruc;

  	estruc=(TipoHistoria*)malloc(sizeof(TipoHistoria));


	}
    	fclose(archivo);


  	}


	temp3=temp3->sig;
  }
}
/**
 *Esta función se encarga de validar que cada uno de los campos de la pestaña de pacientes
 *este llenado.Si es asi entonces procede a insertarlo en la lista dinamica, si no, se creará
 *un cuadro de diálogo donde se le indicara al usuario que dato hace falta de llenar.
 *
 *
 *@author Mirna Cardona
 */
void Agrega(GtkWidget *nom,  gpointer lista)
{char band[35], s, N[20];
  const gchar* Nombre, *direccion, *telefono, *alergias, *padc, *sexo, *nacimiento, *Edad,  *Sangre;
  int  t, e, i;
  float Estatura;
  TipoPaciente *temp, *temp3;
  GtkWidget *dialog;

  temp3=(TipoPaciente*)malloc(sizeof(TipoPaciente));

  TipoLista* datos= (TipoLista*)lista;
  strcpy(band, "\0");
  Nombre=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  if(strcmp(Nombre,"\0")==0)
	strcpy(band, "nombre");
  direccion=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(direccion,"\0")==0)
	strcpy(band, "direccion");
  telefono=gtk_entry_get_text(GTK_ENTRY(datos->lista1[2]));
  if(strcmp(telefono,"\0")==0)
	strcpy(band, "teléfono");
  alergias=gtk_entry_get_text(GTK_ENTRY(datos->lista1[3]));
  if(strcmp(alergias,"\0")==0)
	strcpy(band, "Alergias");
  padc=gtk_entry_get_text(GTK_ENTRY(datos->lista1[4]));
  if(strcmp(padc,"\0")==0)
	strcpy(band, "Padecimientos");
  sexo=gtk_entry_get_text(GTK_ENTRY(datos->lista1[5]));
  if(strcmp(sexo,"\0")==0)
	strcpy(band, "Sexo");
  nacimiento=gtk_entry_get_text(GTK_ENTRY(datos->lista1[6]));
  if(strcmp(nacimiento,"\0")==0)
	strcpy(band, "Fecha de nacimiento");
  Edad=gtk_entry_get_text(GTK_ENTRY(datos->lista1[7]));
  if(strcmp(Edad,"\0")==0)
	strcpy(band, "Edad");
  Estatura=gtk_spin_button_get_value_as_int (datos->lista1[8]);
  if(Estatura<0.5)
	strcpy(band, "Estatura");
  Sangre=gtk_entry_get_text(GTK_ENTRY(datos->lista1[9]));
  if(strcmp(Sangre,"\0")==0)
	strcpy(band, "Sangre");
	strcpy(N, Nombre);
    	for(i=0;i<=strlen(N)-1;i++)
  	{
  	if(N[i]>='a' && N[i]<='z')
            	N[i]=N[i]-'a'+'A';

  	}

//Si es que dalta un dato se crea el cuaro de dialogo, si no, se inserta a la lista.
  if(strcmp(band, "\0")!=0)
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Falta ingresar el dato de %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{
  	strcpy(temp3->nombre,N);
  	strcpy(temp3->direccion,direccion);
  	sscanf(telefono, "%d", &t);
  	temp3->telefono=t;
  	sscanf(sexo, "%c", &s);
  	temp3->sexo=s;
  	strcpy(temp3->fecha,nacimiento);
  	sscanf(Edad, "%d", &e);
  	temp3->edad=e;
  	temp3->estatura=Estatura;
  	strcpy(temp3->alergias,alergias);
  	strcpy(temp3->sangre,Sangre);
  	strcpy(temp3->padecimientos,padc);

  	temp3->sig=NULL;
  	temp3->his=NULL;

  	if(datos->Pac01!=NULL)                                                             	//Si la lista no esta vacia entonces:
  {temp=datos->Pac01;                                                             	//Se le asigna la posición de la primera variable de la lista a una nueva variable temporal
	while(temp->sig!=NULL)                                                     	//Mientras que no se llegue al final de la lista
  	temp=temp->sig;                                                         	//Se aumentará la posición de la variable temporal
	temp->sig=temp3;                                                           	/*Si ya se llego al final entonces al apuntador del ultimo elemento de la lista se le
                     	asigna la variable a la que se le  cargo la información */
  }else
  datos->Pac01=temp3;                                                               	//Si la lista está vacia entonces se le asignará a la primera posición la variable con los datos cargados.

  	gtk_widget_destroy(datos->lista1[10]);
	}

}
void Destroy(GtkWidget *window, gpointer data)
{
  gtk_widget_destroy(data);
}
/**
 *Esta función se encarga de validar que cada uno de los campos de la pestaña de doctores
 *este llenado.Si es asi entonces procede a insertarlo en la lista dinamica, si no, se creará
 *un cuadro de diálogo donde se le indicara al usuario que dato hace falta de llenar.
 *
 *
 *@author Mirna Cardona
 */
void Agrega_D(GtkWidget *nom,  gpointer lista)
{
  char band[35], N[50], te[20];
  const gchar* Nombre, *direccion, *telefono_u, *esp1, *esp2, *estatus, *telefono, *di,  *horario, *consultorio;
  int  t,s, c, i;

  TipoDoctor *temp, *temp3;
  GtkWidget *dialog;

  temp3=(TipoDoctor*)malloc(sizeof(TipoDoctor));

  TipoLista* datos= (TipoLista*)lista;

  strcpy(band, "\0");

  Nombre=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  if(strcmp(Nombre,"\0")==0)
	strcpy(band, "nombre");

 strcpy(N, Nombre);
    	for(i=0;i<=strlen(N)-1;i++)
  	{
  	if(N[i]>='a' && N[i]<='z')
            	N[i]=N[i]-'a'+'A';

  	}

  direccion=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(direccion,"\0")==0)
	strcpy(band, "direccion");

   telefono_u=gtk_entry_get_text(GTK_ENTRY(datos->lista1[2]));
   if(strcmp(telefono_u,"\0")==0)
 	strcpy(band, "Teléfono de urgencias");

  esp1=gtk_entry_get_text(GTK_ENTRY(datos->lista1[3]));
  if(strcmp(esp1,"\0")==0)
	strcpy(band, "Especialidad 1");

	esp2=gtk_entry_get_text(GTK_ENTRY(datos->lista1[4]));
  if(strcmp(esp2,"\0")==0)
	strcpy(band, "Especialidad 2");

   estatus=gtk_entry_get_text(GTK_ENTRY(datos->lista1[5]));
   if(strcmp(estatus,"\0")==0)
	strcpy(band, "Estatus");

  telefono=gtk_entry_get_text(GTK_ENTRY(datos->lista1[6]));
  if(strcmp(telefono,"\0")==0)
	strcpy(band, "Teléfono");

  di=gtk_entry_get_text(GTK_ENTRY(datos->lista1[7]));
  if(strcmp(di,"\0")==0)
	strcpy(band, "Dias de consulta");

  horario=gtk_entry_get_text (GTK_ENTRY(datos->lista1[8]));
	if(horario==0)
	strcpy(band, "Horiario");

  consultorio=gtk_entry_get_text(GTK_ENTRY(datos->lista1[9]));
  if(strcmp(consultorio,"\0")==0)
	strcpy(band, "Consultorio");

  if(strcmp(band, "\0")!=0)
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Falta ingresar el dato de %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{


  	strcpy(temp3->nombre,N);
  	strcpy(temp3->direccion,direccion);

	//strcpy(te, telefono_u);
  	sscanf(telefono_u, "%d", &t);
  	temp3->telefono_urge=t;

  	strcpy(temp3->especialidad1,esp1);
  	strcpy(temp3->especialidad2,esp2);

  	strcpy(temp3->estado,estatus);

	strcpy(te, telefono);
  	if(sscanf(te, "%d", &s)==1);

  	temp3->telefono=s;

  	strcpy(temp3->dias,di);
  	strcpy(temp3->horario,horario);


  	sscanf(consultorio, "%d", &c);
  	temp3->consultorio=c;


  	temp3->sig=NULL;

  	if(datos->Doc01!=NULL)                                                             	//Si la lista no esta vacia entonces:
  {temp=datos->Doc01;                                                             	//Se le asigna la posición de la primera variable de la lista a una nueva variable temporal
	while(temp->sig!=NULL)                                                     	//Mientras que no se llegue al final de la lista
  	temp=temp->sig;                                                         	//Se aumentará la posición de la variable temporal
	temp->sig=temp3;                                                           	/*Si ya se llego al final entonces al apuntador del ultimo elemento de la lista se le
                     	asigna la variable a la que se le  cargo la información */
  }else
  datos->Doc01=temp3;                                                               	//Si la lista está vacia entonces se le asignará a la primera posición la variable con los datos cargados.

  	gtk_widget_destroy(datos->lista1[10]);
	}

}
/**
 *Esta funcion se encarga de obtener la fecha exacta del sistema y
 *lo copia a una cadena de nombre fecha.
 *
 *
 *
 *@author Mirna Cardona
 */

void timestamp(char fecha[20])
{
  time_t t;
  struct tm *tm;
  t=time(NULL);
  tm=localtime(&t);
  strftime(fecha, 100, "%Y/%m/%d-%H:%M", tm);

}
/**
  *Esta función se encarga de validar que cada uno de los campos de la pestaña de historias clínicas
 *este llenado.Si es asi entonces procede a insertarlo en la lista dinamica, si no, se creará
 *un cuadro de diálogo donde se le indicara al usuario que dato hace falta de llenar.
 *
 *
 *@author Mirna Cardona
 */
void Agrega_H(GtkWidget *nom,  gpointer lista)
{char band[35];
  const gchar* Nombre_Doc, *Nombre_Pac, *Diagnostico, *Tratamiento, *Anotaciones, *fecha;
  TipoPaciente *temp;
  TipoHistoria *temp3, *temp2;
  TipoDoctor *doc;
  int i;
  char Nombre[20], nombre_doctor[40];
   GtkWidget *dialog;

  TipoLista *datos= (TipoLista*)lista;
  doc=datos->Doc01;
  temp=datos->Pac01;

 temp3=(TipoHistoria*)malloc(sizeof(TipoHistoria));
  strcpy(band, "\0");

  Nombre_Doc=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  if(strcmp(Nombre_Doc,"\0")==0)
	strcpy(band, "Nombre del doctor");

  Nombre_Pac=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(Nombre_Pac,"\0")==0)
	strcpy(band, "Nombre del Paciente");

  fecha=gtk_label_get_text(GTK_LABEL(datos->lista1[2]));
  Diagnostico=gtk_entry_get_text(GTK_ENTRY(datos->lista1[3]));
  if(strcmp(Diagnostico,"\0")==0)
	strcpy(band, "Diagnóstico");


  Tratamiento=gtk_entry_get_text(GTK_ENTRY(datos->lista1[4]));
  if(strcmp(Tratamiento,"\0")==0)
	strcpy(band, "Tratamiento");


  Anotaciones=gtk_entry_get_text(GTK_ENTRY(datos->lista1[5]));
  if(strcmp(Anotaciones,"\0")==0)
	strcpy(band, "Anotaciones");

  strcpy(Nombre,Nombre_Pac);
  for(i=0;i<=strlen(Nombre)-1;i++)
  	{
  	if(Nombre[i]>='a' && Nombre[i]<='z')
            	Nombre[i]=Nombre[i]-'a'+'A';

  	}
 strcpy(nombre_doctor,Nombre_Doc);
  for(i=0;i<=strlen(nombre_doctor)-1;i++)
  	{
  	if(nombre_doctor[i]>='a' && nombre_doctor[i]<='z')
            	nombre_doctor[i]=nombre_doctor[i]-'a'+'A';

  	}

  if(strcmp(band, "\0")!=0)
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Falta ingresar el dato de %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{
  	while(temp!=NULL&&strcmp(temp->nombre, Nombre)!=0)
  temp=temp->sig;

  	if(temp!=NULL)
  {


	while(doc!=NULL&&strcmp(doc->nombre, nombre_doctor)!=0)
  	doc=doc->sig;

	if(doc!=NULL)
  	{

    	strcpy(temp3->fecha,fecha);

    	strcpy(temp3->nombre_d,Nombre_Doc);
    	strcpy(temp3->nombre_p,Nombre);

    	strcpy(temp3->diagnostico,Diagnostico);
    	strcpy(temp3->tratamiento,Tratamiento);

    	strcpy(temp3->anotaciones,Anotaciones);

    	temp3->sig=NULL;

    	if(temp->his!=NULL)                                                             	//Si la lista no esta vacia entonces:
	{temp2=temp->his;                                                             	//Se le asigna la posición de la primera variable de la lista a una nueva variable temporal
  	while(temp2->sig!=NULL)                                                     	//Mientras que no se llegue al final de la lista
    	temp2=temp2->sig;                                                         	//Se aumentará la posición de la variable temporal

  	temp3->numero=(temp2->numero)+1;
  	temp2->sig=temp3;                                                           	/*Si ya se llego al final entonces al apuntador del ultimo elemento de la lista se le
                        	asigna la variable a la que se le  cargo la información */
	}else
	{
  	temp3->numero=1;
  	temp->his=temp3;                                                               	//Si la lista está vacia entonces se le asignará a la primera posición la variable con los datos cargados.

	}

    	gtk_widget_destroy(datos->lista1[10]);
        	}
	else
        	{

          	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El doctor no esta dado de alta");
          	gtk_dialog_run(GTK_DIALOG(dialog));
          	gtk_widget_destroy(dialog);

        	}

  }
  	else
  {

	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no esta dado de alta");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
  }



	}
}
/**
 *
 *Plasmar se encarga de abrir los archivos de doctores, pacientes e historias en modo "wt"
 *el cual eliminara el contenido de las historias y creará un nuevo archivo con la información
 *de cada lista dinámica.
 *
 *@author Mirna Cardona
 */
void  plasma(TipoLista *datos)
{
  FILE *archivo;
  TipoDoctor *temp;
  TipoPaciente *temp3;
  TipoHistoria *h;
  int i;
  char cad[20];

  archivo=fopen("doctores", "wt");
  temp=datos->Doc01;

  while(temp!=NULL)
	{fprintf(archivo, "Nombre: %s\n", temp->nombre);
  	fprintf(archivo, "Especialidad 1: %s\n", temp->especialidad1);
  	fprintf(archivo, "Especialidad 2: %s\n", temp->especialidad2);
  	fprintf(archivo, "Estado: %s\n", temp->estado);
  	fprintf(archivo, "Telefono de urgencias: %d\n", temp->telefono_urge);
  	fprintf(archivo, "Direccion: %s\n", temp->direccion);
  	fprintf(archivo, "Telefono: %d\n", temp->telefono);
  	fprintf(archivo, "Consultorio: %d\n", temp->consultorio);
  	fprintf(archivo, "Dias: %s\n", temp->dias);
  	fprintf(archivo, "Horario: %s\n", temp->horario);
  	temp=temp->sig;
	}
  fclose(archivo);


  archivo=fopen("pacientes", "wt");
  temp3=datos->Pac01;
  while(temp3!=NULL)
	{fprintf(archivo, "Nombre: %s\n", temp3->nombre);
  	fprintf(archivo, "Direccion: %s\n", temp3->direccion);
  	fprintf(archivo, "Telefono: %d\n", temp3->telefono);
  	fprintf(archivo, "Sexo: %c\n", temp3->sexo);
  	fprintf(archivo, "Fecha: %s\n", temp3->fecha);
  	fprintf(archivo, "Edad: %d\n", temp3->edad);
  	fprintf(archivo, "Estatura: %f\n", temp3->estatura);
  	fprintf(archivo, "Alergias: %s\n", temp3->alergias);
  	fprintf(archivo, "Sangre: %s\n", temp3->sangre);
  	fprintf(archivo, "Padecimientos: %s\n", temp3->padecimientos);

  	temp3=temp3->sig;
	}
  fclose(archivo);

  temp3=datos->Pac01;

  while(temp3!=NULL)
	{
  	h=temp3->his;

  	strcpy(cad,temp3->nombre);
  	for(i=0;i<=strlen(cad);i++)
  {if(cad[i]==' ')
  	cad[i]='_';
  }
  	archivo=fopen(cad,"wt");

  	while(h!=NULL)
  {

	fprintf(archivo,"Nombre de paciente: %s\n", h->nombre_p);
	fprintf(archivo, "Nombre de Doctor: %s\n", h->nombre_d);
	fprintf(archivo, "Fecha: %s\n", h->fecha);
	fprintf(archivo, "Diagnostico: %s\n", h->diagnostico);
	fprintf(archivo, "Tratamiento: %s\n", h->tratamiento);
	fprintf(archivo, "Anotaciones: %s\n", h->anotaciones);
	fprintf(archivo, "Numero de Ficha: %d\n",h->numero);
	h=h->sig;
  }
  	fclose(archivo);

  	temp3=temp3->sig;
	}
}
/**
 *
 *Esta funcion crea la interfaz gráica de una ventana en la que se le pregunta al
 *usuario el nombre del paciente del cuál quiere consultar la historia clinica y también
 *un boton al que se le conecta la funcion de Todas_H.
 *
 *@author Mirna Cardona
 */
void Desplegar_His(GtkWidget *menu, gpointer lista)
{
  GtkWidget  *label, *box, *vebox, *nom, *box1;

  TipoLista *datos= (TipoLista*)lista;

  box=gtk_hbox_new(TRUE, 0);
  datos->lista1[0]= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(datos->lista1[0]),320,200);
  gtk_container_border_width(GTK_CONTAINER(datos->lista1[0]),5);


  label=gtk_label_new("Nombre del paciente: ");
  datos->lista1[1]=gtk_entry_new();

  nom= gtk_button_new_with_label("Buscar");
  gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Todas_H),datos);
  gtk_widget_show(nom);


  gtk_box_pack_start(GTK_BOX(box), label,TRUE, FALSE, 10);

  gtk_box_pack_start(GTK_BOX(box), datos->lista1[1],TRUE, FALSE, 10);

  vebox=gtk_vbox_new(TRUE, 0);


  gtk_box_pack_start(GTK_BOX(vebox), box,TRUE, FALSE, 10);

  box1=gtk_hbox_new(TRUE, 0);
  box=gtk_hbox_new(TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), box1,TRUE, FALSE, 10);
  gtk_box_pack_end(GTK_BOX(box), nom,FALSE, FALSE, 10);
  gtk_box_pack_end(GTK_BOX(vebox), box,TRUE, FALSE, 10);


  gtk_container_add (GTK_CONTAINER (datos->lista1[0]), vebox);
  gtk_signal_connect(GTK_OBJECT(datos->lista1[0]),"destroy",GTK_SIGNAL_FUNC(Destroy),datos->lista1[0]);

  gtk_widget_show_all (datos->lista1[0]);

}
/**
 *
 *Todas_H se encarga de validar que el nombre de usuario tenga texto y si es asi entonces lo convierte a mayusculas
 *después valida que el numero de ficha sea un caracter válido (de tipo entero). Teniendo estos datos valida que en
 *la lista dinámica exista ese nombre de usuario y si no es así despliega un cuadro de texto para hacerle saber al usuario
 *que el paciente no existe. Despues valida si ese paciente tiene historias clínicas, si las tiene abre una pesataña con
 *la información principal del paciente y un boton siguiente que recorrerá la lista dinamica de sus historias clínicas.
 *Si no tiene historias dadas de altas se despliega otro cuadro de texto el cual informa al usuario que no cuenta con
 *historias clínicas.
 *El botón que se encarga de "avanzar" en las historias tiene como señal la funcion Avanza_H.
 *
 *@author Mirna Cardona
 */
void Todas_H(GtkWidget *menu, gpointer lista)
{
  GtkWidget  *vbox, *nom, *dialog;
  TipoPaciente *temp;
  char band[40], Nombre[20], cad[500];
  const gchar* Nombre_P;
  TipoHistoria *His;
  TipoLista *datos= (TipoLista*)lista;

  int i;
  temp=datos->Pac01;
  strcpy(band, "\0");

  Nombre_P=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(Nombre_P,"\0")==0)
	strcpy(band, "Nombre del paciente");
  else
	{



  	strcpy(Nombre,Nombre_P);
  	for(i=0;i<=strlen(Nombre_P)-1;i++)
  {
	if(Nombre[i]>='a' && Nombre[i]<='z')
  	Nombre[i]=Nombre[i]-'a'+'A';

  }
	}

  if(strcmp(band, "\0")!=0)
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor ingresa el nombre del Paciente");
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}


  else
	{while(temp!=NULL&&strcmp(Nombre, temp->nombre)!=0)
  temp=temp->sig;

  	if(temp!=NULL)
  {
	if(temp->his!=NULL)
  	{His=temp->his;
    	datos->His=His;

    	datos->lista1[3]= gtk_window_new (GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_default_size(GTK_WINDOW(datos->lista1[3]),320,200);
    	gtk_container_border_width(GTK_CONTAINER(datos->lista1[3]),5);


     	vbox=gtk_vbox_new(TRUE, 0);
     	sprintf(cad,"Datos del Paciente:                      	\n\nNombre del Paciente: %s\nDireccion: %s\nTelefono: %d\nPadecimientos: %s\nSangre: %s\nEstatura: %f\nAlergias: %s\n", temp->nombre, temp->direccion, temp->telefono, temp->padecimientos, temp->sangre, temp->estatura, temp->alergias);

    	datos->lista1[4]=gtk_label_new(cad);


    	gtk_signal_connect(GTK_OBJECT(datos->lista1[3]),"destroy",GTK_SIGNAL_FUNC(Destroy),datos->lista1[3]);



    	nom= gtk_button_new_with_label("Siguiente");
    	gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Avanza_H),datos);
    	gtk_widget_show(nom);

    	gtk_box_pack_start(GTK_BOX(vbox), datos->lista1[4],TRUE, FALSE, 10);
    	gtk_box_pack_start(GTK_BOX(vbox), nom,TRUE, FALSE, 10);

    	gtk_container_add (GTK_CONTAINER (datos->lista1[3]), vbox);
     	gtk_widget_show_all (datos->lista1[3]);

  	}
	else
  	{

    	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no tiene historias dadas de alta");
    	gtk_dialog_run(GTK_DIALOG(dialog));
    	gtk_widget_destroy(dialog);

  	}
  }else
  {

	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no esta dado de alta");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

  }

	}


}
/**
 *Avanza_H recibe como parametro una estructura que contiene el apuntador al inicio de la lista dinamica de las
 *historias clínicas del paciente al que se busco con Desplegar_His. Con esta información cada que el usuario quiera
 *avanzar en Todas_H se copara a una cadena de texto la informacion de la historia clinica y se cambiara el label de
 *Todas_H que esta almacenado en la posicion del arreglo 4.
 *Una vez hecho esto se recorrera la posición de la lista dinámica.
 *
 *@author Mirna Cardona
 */
void Avanza_H(GtkWidget *menu, gpointer lista)
{
  char cad[500];

TipoLista *datos= (TipoLista*)lista;


 sprintf(cad,  "Fecha de la cita: %s 	Numero de ficha: %d\n\nNombre del doctor: %s\n\nDiagnostico: %s\n\nTratamiento: %s\n\nIndicaciones: %s\n", datos->His->fecha,datos->His->numero,  datos->His->nombre_d, datos->His->diagnostico, datos->His->tratamiento, datos->His->anotaciones);

gtk_label_set_text (GTK_LABEL(datos->lista1[4]),cad);
if(datos->His->sig!=NULL)
datos->His=datos->His->sig;
}
/**
 *
 *Consult_His genera una interfáz gráfica en la cual se le pide al usuario el nombre del paciente de quien se quiere
 *buscar la ficha y el numero de ficha que desea consultar.
 *Se crea un boton de buscar que se conecta con la función Busca_H.
 *
 *@author Mirna Cardona
 */
void consult_His(GtkWidget *nom,  gpointer lista)
{

  GtkWidget *label, *box, *vebox,*button, *box1;

  TipoLista *datos= (TipoLista*)lista;

  box=gtk_hbox_new(TRUE, 0);
  datos->lista1[0]= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(datos->lista1[0]),320,200);
  gtk_container_border_width(GTK_CONTAINER(datos->lista1[0]),15);


  label=gtk_label_new("Nombre del paciente: ");
  datos->lista1[1]=gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(box), label,TRUE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), datos->lista1[1],TRUE, FALSE, 0);

  label=gtk_label_new("Numero de Ficha: ");
  datos->lista1[2]=gtk_entry_new();


  gtk_box_pack_start(GTK_BOX(box), label,TRUE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), datos->lista1[2],TRUE, FALSE, 0);

  button= gtk_button_new_with_label("Buscar");
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Busca_H),datos);
  gtk_widget_show(button);

  vebox=gtk_vbox_new(TRUE, 0);


  gtk_box_pack_start(GTK_BOX(vebox), box,TRUE, FALSE, 0);

  box1=gtk_hbox_new(TRUE, 0);
  box=gtk_hbox_new(TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), box1,TRUE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(box), button,TRUE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(vebox), box,TRUE, FALSE, 0);


  gtk_container_add (GTK_CONTAINER (datos->lista1[0]), vebox);
  gtk_signal_connect(GTK_OBJECT(datos->lista1[0]),"destroy",GTK_SIGNAL_FUNC(Destroy),datos->lista1[0]);

  gtk_widget_show_all (datos->lista1[0]);

}
/**
 *
 *Esta funcion se encarga de verificar que los campos de la función Consul_His tengar datos valido, tanto para que se 
 *verifique que no estan vacios como que en el numero de ficha se tenga un caracter numerico. una vez que se verifica esto se compara en la
 *lista dinámica si el nombre del paciente que dio el usuario si existe en la lista dinámica, si no le avisa al usuario. Después 
 *verifica que el usuario tenga el numero de historia dado. Si es asi entonces despliega la historia. 
 *
 *@author Mirna Cardona
 */

void Busca_H(GtkWidget *menu, gpointer lista)
{
 GtkWidget *window, *label, *vbox, *nom, *dialog;
  TipoPaciente *temp;
  char band[40], Num[20], cad[500], Nombre[50];
  const gchar* Nombre_P, *numero;
  TipoHistoria *His;
  TipoLista *datos= (TipoLista*)lista;

  int i, n;
  temp=datos->Pac01;
  strcpy(band, "\0");

  Nombre_P=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(Nombre_P,"\0")==0)
	strcpy(band, "Nombre del paciente");


  numero=gtk_entry_get_text(GTK_ENTRY(datos->lista1[2]));
  if(strcmp(numero,"\0")==0)
	strcpy(band, "Numeero de ficha");


  if(strcmp(band, "\0")!=0)
	{
  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor ingresa el %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{

  	strcpy(Num, numero);

  	if(sscanf(Num, "%d", &n)!=1)

  {

	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor ingresa un numero de ficha valido");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

  }   else
  {

	strcpy(Nombre,Nombre_P);
	for(i=0;i<=strlen(Nombre_P)-1;i++)
  	{
    	if(Nombre[i]>='a' && Nombre[i]<='z')
	Nombre[i]=Nombre[i]-'a'+'A';

  	}


  while(temp!=NULL&&strcmp(Nombre, temp->nombre)!=0)
  temp=temp->sig;

  if(temp!=NULL)
	{
  	if(temp->his!=NULL)
    	{His=temp->his;

	while(His!=NULL&&His->numero!=n)
  	His=His->sig;

	if(His!=NULL)
  	{

    	window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_default_size(GTK_WINDOW(window),320,200);
    	gtk_container_border_width(GTK_CONTAINER(window),5);

    	vbox=gtk_vbox_new(TRUE, 0);
    	sprintf(cad,"Datos del Paciente:                      	\n\nNombre del Paciente: %s\nDireccion: %s\n\nTelefono: %d\nPadecimientos: %s\nSangre: %s\nEstatura: %f\nAlergias: %s\n", temp->nombre, temp->direccion, temp->telefono, temp->padecimientos, temp->sangre, temp->estatura, temp->alergias);

    	label=gtk_label_new(cad);
    	gtk_box_pack_start(GTK_BOX(vbox), label,TRUE, FALSE, 10);



    	sprintf(cad,"Datos de la Ficha:\n\nFecha de la cita: %s 	Numero de ficha: %d\n\nNombre del doctor: %s\n\nDiagnostico: %s\n\nTratamiento: %s\n\nIndicaciones: %s\n", His->fecha,His->numero, His->nombre_d, His->diagnostico, His->tratamiento, His->anotaciones);

    	label=gtk_label_new(cad);
    	gtk_box_pack_start(GTK_BOX(vbox), label,TRUE, FALSE, 10);



    	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);

    	nom= gtk_button_new_with_label("Aceptar");
    	gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Destroy),window);
    	gtk_widget_show(nom);


    	gtk_box_pack_start(GTK_BOX(vbox), nom,TRUE, FALSE, 10);

    	gtk_container_add (GTK_CONTAINER (window), vbox);
    	gtk_widget_show_all (window);

  	}
	else
  	{
    	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El no tiene el numero de historia");
    	gtk_dialog_run(GTK_DIALOG(dialog));
    	gtk_widget_destroy(dialog);

  	}
    	}
  	else
    	{

	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no tiene historias dadas de alta");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

    	}
	}else
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no esta dado de alta");
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  
  }
	
	}
  
}
/**
 *
 *Mod_His se encarga de generar una interfaz gráfica donde se le pregunte al usuario el nombre del paciente y el 
 *numero de historia clínica que desea modificar. Se conecta por medio de un boton la función de Editar_His.
 *
 *
 *@author Mirna Cardona
 */

///////////////
void Mod_His(GtkWidget *menu, gpointer lista)
{

 GtkWidget *label, *box, *vebox,*button, *box1;

  TipoLista *datos= (TipoLista*)lista;

  box=gtk_hbox_new(TRUE, 0);
  datos->lista1[9]= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(datos->lista1[9]),320,200);
  gtk_container_border_width(GTK_CONTAINER(datos->lista1[9]),15);


  label=gtk_label_new("Nombre del paciente: ");
  datos->lista1[0]=gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(box), label,TRUE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), datos->lista1[0],TRUE, FALSE, 0);

  label=gtk_label_new("Numero de Ficha: ");
  datos->lista1[1]=gtk_entry_new();


  gtk_box_pack_start(GTK_BOX(box), label,TRUE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), datos->lista1[1],TRUE, FALSE, 0);

  button= gtk_button_new_with_label("Buscar");
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Editar_His),datos);
  gtk_widget_show(button);

  vebox=gtk_vbox_new(TRUE, 0);

  gtk_box_pack_start(GTK_BOX(vebox), box,TRUE, FALSE, 0);

  box1=gtk_hbox_new(TRUE, 0);
  box=gtk_hbox_new(TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), box1,TRUE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(box), button,TRUE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(vebox), box,TRUE, FALSE, 0);


  gtk_container_add (GTK_CONTAINER (datos->lista1[9]), vebox);
  gtk_signal_connect(GTK_OBJECT(datos->lista1[9]),"destroy",GTK_SIGNAL_FUNC(Destroy),datos->lista1[9]);

  gtk_widget_show_all (datos->lista1[9]);
}
/**
 *
 *Editar_His va a verificar que se introduzca un nombre y numero de ficha válidos. Si es asi entonces 
 *ve si encuentra el nombre del paciente en la lista dinámica de los pacientes. Luego verifica si el paciente tiene 
 *la historia que se quiere modificar. Si es asi despliega una interfaz gráfica con los datos de esa historia 
 *Se le conecta la función de Cambiar_H a un boton.
 *
 *@author Mirna Cardona
 */
void Editar_His(GtkWidget *menu, gpointer lista)
{


  GtkWidget  *label, *vbox, *nom, *dialog, *box;
  TipoPaciente *temp;
  char band[40], Num[20], fecha[50], Nombre[50], deq[30];
  const gchar* Nombre_P, *numero;
  TipoHistoria *His;
  int i, n;
  TipoLista *datos= (TipoLista*)lista;



  temp=datos->Pac01;
  strcpy(band, "\0");

  Nombre_P=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  if(strcmp(Nombre_P,"\0")==0)
	strcpy(band, "Nombre del paciente");


  numero=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(numero,"\0")==0)
	strcpy(band, "Numeero de ficha");


  if(strcmp(band, "\0")!=0)
	{
  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor ingresa el %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{

  	strcpy(Num, numero);

  	if(sscanf(Num, "%d", &n)!=1)

  {

	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor ingresa un numero de ficha valido");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

  }   else
  {

	strcpy(Nombre,Nombre_P);
	for(i=0;i<=strlen(Nombre_P)-1;i++)
  	{
    	if(Nombre[i]>='a' && Nombre[i]<='z')
	Nombre[i]=Nombre[i]-'a'+'A';

  	}


	while(temp!=NULL&&strcmp(Nombre, temp->nombre)!=0)
  	temp=temp->sig;

	if(temp!=NULL)
  	{
    	if(temp->his!=NULL)
	{His=temp->his;

  	while(His!=NULL&&His->numero!=n)
    	His=His->sig;

  	if(His!=NULL)
    	{

      	datos->lista1[10] = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      	gtk_window_set_title (GTK_WINDOW (datos->lista1[10]), "Alta de Historias");
      	gtk_container_set_border_width (GTK_CONTAINER (datos->lista1[10]), 10);

      	sprintf(deq,"Datos de la cita #%d:", His->numero);
      	datos->lista1[6] = gtk_label_new (deq);

      	vbox = gtk_vbox_new (FALSE, 5);
      	gtk_box_pack_start_defaults (GTK_BOX (vbox), datos->lista1[6]);

      	box = gtk_hbox_new(FALSE,5);
      	label = gtk_label_new ("Nombre del Doctor:");

      	datos->lista1[0]= gtk_label_new (His->nombre_d);
      	//gtk_label_set_text (GTK_LABEL(datos->lista1[0]), His->nombre_d);
      	gtk_box_pack_start_defaults (GTK_BOX (box), label);
      	gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[0]);

      	label = gtk_label_new ("Nombre del Paciente:");
      	datos->lista1[1]= gtk_label_new (His->nombre_p);
      	//gtk_entry_set_text (GTK_ENTRY(datos->lista1[1]), His->nombre_p);
      	gtk_box_pack_start_defaults (GTK_BOX (box), label);
      	gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[1]);

      	gtk_box_pack_start_defaults (GTK_BOX (vbox), box);
      	box = gtk_hbox_new(FALSE,5);

      	timestamp(fecha);

      	label = gtk_label_new ("Fecha de la cita:");
      	gtk_box_pack_start_defaults (GTK_BOX (box), label);
      	datos->lista1[2] = gtk_label_new (His->fecha);
      	gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[2]);

      	gtk_box_pack_start_defaults (GTK_BOX (vbox), box);

      	box = gtk_hbox_new(TRUE,5);
      	label = gtk_label_new ("Diagnostico:");
      	datos->lista1[3] = gtk_entry_new ();
      	gtk_entry_set_text (GTK_ENTRY(datos->lista1[3]), His->diagnostico);
      	gtk_box_pack_start_defaults (GTK_BOX (box), label);
      	gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[3]);

      	label = gtk_label_new ("Tratamiento:");
      	datos->lista1[4] = gtk_entry_new ();
      	gtk_entry_set_text (GTK_ENTRY(datos->lista1[4]), His->tratamiento);
      	gtk_box_pack_start_defaults (GTK_BOX (box), label);
      	gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[4]);


      	label = gtk_label_new ("Anotaciones:");
      	datos->lista1[5] = gtk_entry_new ();
      	gtk_entry_set_text (GTK_ENTRY(datos->lista1[5]), His->anotaciones);
      	gtk_box_pack_start_defaults (GTK_BOX (box), label);
      	gtk_box_pack_start_defaults (GTK_BOX (box), datos->lista1[5]);

      	gtk_box_pack_start_defaults (GTK_BOX (vbox), box);


      	nom= gtk_button_new_with_label("Aceptar");
      	gtk_box_pack_start(GTK_BOX(vbox),nom,TRUE,TRUE,0);
      	gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Cambiar_H),datos);
      	gtk_widget_show(nom);


      	gtk_container_add (GTK_CONTAINER (datos->lista1[10]), vbox);

      	gtk_signal_connect(GTK_OBJECT(datos->lista1[10]),"destroy",GTK_SIGNAL_FUNC(Destroy),datos->lista1[10]);
      	gtk_widget_show_all (datos->lista1[10]);


    	}
  	else
    	{
      	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El no tiene el numero de historia");
      	gtk_dialog_run(GTK_DIALOG(dialog));
      	gtk_widget_destroy(dialog);

    	}
	}
    	else
    	{

	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no tiene historias dadas de alta");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

    	}
  	}else
  	{

    	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no esta dado de alta");
    	gtk_dialog_run(GTK_DIALOG(dialog));
    	gtk_widget_destroy(dialog);

  	}

  }

	}

}



/**
 *
 *Cambiar_H verifica que todos los campos tengar información válida y si es asi cambia los datos de la historia 
 *clínica en la lista dinámica. 
 *
 *
 *@author Mirna Cardona
 */
void Cambiar_H(GtkWidget *menu, gpointer lista)
{
char band[35];
 const gchar* Nombre_Doc, *Nombre_Pac, *Diagnostico, *Tratamiento, *Anotaciones, *numero;
  TipoPaciente *temp;
  TipoHistoria *temp3;
  int i, num;
  char Nombre[20];
   GtkWidget *dialog;

  TipoLista *datos= (TipoLista*)lista;

  temp=datos->Pac01;


  strcpy(band, "\0");

  Nombre_Doc=gtk_label_get_text(GTK_LABEL(datos->lista1[0]));
  if(strcmp(Nombre_Doc,"\0")==0)
	strcpy(band, "Nombre del doctor");

  Nombre_Pac=gtk_label_get_text(GTK_LABEL(datos->lista1[1]));
  if(strcmp(Nombre_Pac,"\0")==0)
	strcpy(band, "Nombre del Paciente");


  Diagnostico=gtk_entry_get_text(GTK_ENTRY(datos->lista1[3]));
  if(strcmp(Diagnostico,"\0")==0)
	strcpy(band, "Diagnóstico");


  Tratamiento=gtk_entry_get_text(GTK_ENTRY(datos->lista1[4]));
  if(strcmp(Tratamiento,"\0")==0)
	strcpy(band, "Tratamiento");


  Anotaciones=gtk_entry_get_text(GTK_ENTRY(datos->lista1[5]));
  if(strcmp(Anotaciones,"\0")==0)
	strcpy(band, "Anotaciones");

  strcpy(Nombre,Nombre_Pac);
  for(i=0;i<=strlen(Nombre)-1;i++)
	{
  	if(Nombre[i]>='a' && Nombre[i]<='z')
	Nombre[i]=Nombre[i]-'a'+'A';

	}


  if(strcmp(band, "\0")!=0)
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Falta ingresar el dato de %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{numero=gtk_label_get_text(GTK_LABEL(datos->lista1[6]));
  	strcpy(band, numero);
  	sscanf(band, "Datos de la cita #%d:", &num);
  	while(temp!=NULL&&strcmp(temp->nombre, Nombre)!=0)
	temp=temp->sig;

  	if(temp!=NULL)
	{///////////////////
  	temp3=temp->his;
  	while(temp3!=NULL&&temp3->numero!=num)
    	temp3=temp3->sig;

  	strcpy(temp3->diagnostico,Diagnostico);
  	strcpy(temp3->tratamiento,Tratamiento);

  	strcpy(temp3->anotaciones,Anotaciones);

	}
  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Cambio guardado con exito");
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

  	gtk_widget_destroy(datos->lista1[9]);
  	gtk_widget_destroy(datos->lista1[10]);
	}

}


/**
 *Busca_D
 *Una vez que se recibe el nombre del doctor a modificar, se pasa a esta
 *función para que sea buscado en la lista dinámica, en caso de encontrarlo
 *abrira la ventana para realizar la modificacion, posterior a eso, llamara a
 *la funcion Cambiar_D.
 *
 *
 *@author JuanP Gomez
 */

void Busca_D(GtkWidget *menu, gpointer lista)
{
  GtkWidget *window, *label, *vbox, *nom, *dialog,*box,*vbox1,*vbox2,*box1;
  TipoDoctor *temp;
  char band[40], Nombre[50], tel[20], tel_u[20], cons[20];
  const gchar* Nombre_D;
  TipoLista *datos= (TipoLista*)lista;

  int i;
  temp=datos->Doc01;
  strcpy(band, "\0");

  Nombre_D=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  if(strcmp(Nombre_D,"\0")==0)
	strcpy(band, "Nombre del doctor");



  if(strcmp(band, "\0")!=0)
	{
  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor ingresa el %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);
	}
  else
  {

	strcpy(Nombre,Nombre_D);
	for(i=0;i<=strlen(Nombre_D)-1;i++)
  	{
    	if(Nombre[i]>='a' && Nombre[i]<='z')
      	Nombre[i]=Nombre[i]-'a'+'A';

  	}


	while(temp!=NULL&&strcmp(Nombre, temp->nombre)!=0)
  	temp=temp->sig;


	if(temp!=NULL)
  	{

    	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_title (GTK_WINDOW (window), "Modificacion de Doctores");
    	gtk_container_set_border_width (GTK_CONTAINER (window), 10);


    	label = gtk_label_new ("Datos del Doctor:");

    	vbox = gtk_vbox_new (FALSE, 5);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox), label);


    	label = gtk_label_new ("Nombre:");
    	nom = gtk_label_new (temp->nombre);
    	// gtk_entry_set_text(GTK_LABEL(nom),Nombre);
    	datos->lista1[0] = nom;
    	// gtk_entry_set_visibility (GTK_ENTRY (nom), TRUE);




    	box=gtk_vbox_new(FALSE, 5);

    	vbox1 = gtk_hbox_new (FALSE, 5);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[0]);
    	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

    	vbox1 = gtk_hbox_new (FALSE, 5);

    	label = gtk_label_new ("Direccion:");
    	datos->lista1[1] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[1]),temp->direccion);
    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[1]), TRUE);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[1]);
    	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


    	sprintf(tel_u,"%d", temp->telefono_urge);



    	//////////
    	label = gtk_label_new ("Telefono de urgencias:");
    	datos->lista1[2] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[2]),tel_u);


    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[2]), TRUE);


    	vbox1 = gtk_hbox_new (FALSE, 5);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[2]);
    	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

    	label = gtk_label_new ("Especialidad 1:");
    	datos->lista1[3] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[3]),temp->especialidad1);
    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[3]), TRUE);


    	vbox1 = gtk_hbox_new (FALSE, 5);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[3]);
    	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


    	label = gtk_label_new ("Especialidad 2:");
    	datos->lista1[4] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[4]),temp->especialidad2);
    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[4]), TRUE);


    	vbox1 = gtk_hbox_new (FALSE, 5);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[4]);
    	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


    	vbox2 = gtk_vbox_new (FALSE, 5);

    	label = gtk_label_new ("Estatus:");
    	datos->lista1[5] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[5]),temp->estado);
    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[5]), TRUE);


    	vbox1=gtk_hbox_new(TRUE,5);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[5]);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);


    	sprintf(tel, "%d", temp->telefono);
    	/////////////7
    	label = gtk_label_new ("Telefono:");
    	datos->lista1[6] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[6]),tel);
    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[6]), TRUE);


    	vbox1=gtk_hbox_new(FALSE,5);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[6]);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

    	label = gtk_label_new ("Dias de consulta:");
    	datos->lista1[7] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[7]),temp->dias);
    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[7]), TRUE);


    	vbox1=gtk_hbox_new(FALSE,5);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[7]);

    	label = gtk_label_new ("Horiario:");

    	datos->lista1[8] = gtk_entry_new();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[8]),temp->horario);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[8]);


      	sprintf(cons, "%d", temp->consultorio);
    	/////////
    	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);
    	label = gtk_label_new ("Consultorio:");
    	datos->lista1[9] = gtk_entry_new ();
    	gtk_entry_set_text(GTK_ENTRY(datos->lista1[9]),cons);
    	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[9]), TRUE);


    	vbox1=gtk_hbox_new(FALSE,5);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
    	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[9]);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);


    	datos->lista1[10]=window;

    	nom= gtk_button_new_with_label("Aceptar");
    	gtk_box_pack_start(GTK_BOX(vbox2),nom,FALSE,TRUE,0);
    	gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Cambiar_D),datos);
    	gtk_widget_show(nom);

    	box1=gtk_hbox_new(TRUE,5);
    	// gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);
    	gtk_box_pack_start_defaults (GTK_BOX (box1), box);
    	gtk_box_pack_start_defaults (GTK_BOX (box1), vbox2);

    	gtk_box_pack_start_defaults (GTK_BOX (vbox), box1);

    	gtk_container_add (GTK_CONTAINER (window), vbox);

    	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
    	gtk_widget_show_all (window);


  	}else
  	{

    	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El doctor no esta dado de alta");
    	gtk_dialog_run(GTK_DIALOG(dialog));
    	gtk_widget_destroy(dialog);

  	}

  }

}

/**
 *Cambiar_D
 *Se encarga de verificar que todos los campos que se modifiquen esten llenos
 *en caso de no estar lleno alguno, se regresarán diálogos para advertir al
 *usuario, cuando se llene correctamente va a sustituir los cambios en la lista
 *dinamica.
 *
 *
 *@author JuanP Gomez
 */

void Cambiar_D(GtkWidget *menu, gpointer lista)
{
  char band[35], Nombre[20],tel_u[50], tel_n[50], consultorio[50];

  const gchar* Nombre_D, *direccion, *espe1, *espe2, *estatus,*dias,*horario,  *tel, *tel_urg, *consul;
  TipoDoctor *temp;
  int i, n_u, n_n, c;
  GtkWidget *dialog;

  TipoLista *datos= (TipoLista*)lista;

  temp=datos->Doc01;


  strcpy(band, "\0");

  Nombre_D=gtk_label_get_text(GTK_LABEL(datos->lista1[0]));
  /*if(strcmp(Nombre_D,"\0")==0)
	strcpy(band, "Nombre del doctor");*/

  direccion=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(direccion,"\0")==0)
	strcpy(band, "Direccion");


  tel_urg=gtk_entry_get_text(GTK_ENTRY(datos->lista1[2]));
  if(strcmp(tel_urg,"\0")==0)
  strcpy(band, "Telefono urgencias");


  espe1=gtk_entry_get_text(GTK_ENTRY(datos->lista1[3]));
  if(strcmp(espe1,"\0")==0)
	strcpy(band, "Especialidad 1");


  espe2=gtk_entry_get_text(GTK_ENTRY(datos->lista1[4]));
  if(strcmp(espe2,"\0")==0)
  strcpy(band, "Especialidad 2");

  estatus=gtk_entry_get_text(GTK_ENTRY(datos->lista1[5]));
  if(strcmp(estatus,"\0")==0)
  strcpy(band, "Estatus");

  tel=gtk_entry_get_text(GTK_ENTRY(datos->lista1[6]));
  if(strcmp(tel,"\0")==0)
  strcpy(band, "Telefono");

  dias=gtk_entry_get_text(GTK_ENTRY(datos->lista1[7]));
  if(strcmp(dias,"\0")==0)
  strcpy(band, "Dias habiles");

  horario=gtk_entry_get_text(GTK_ENTRY(datos->lista1[8]));
  if(strcmp(horario,"\0")==0)
  strcpy(band, "Horario");

  consul=gtk_entry_get_text(GTK_ENTRY(datos->lista1[9]));
  if(strcmp(consul,"\0")==0)
  strcpy(band, "consultorio");






  strcpy(Nombre,Nombre_D);
  for(i=0;i<=strlen(Nombre)-1;i++)
	{
  	if(Nombre[i]>='a' && Nombre[i]<='z')
	Nombre[i]=Nombre[i]-'a'+'A';

	}


  if(strcmp(band, "\0")!=0)
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Falta ingresar el dato de %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{
  	while(temp!=NULL&&strcmp(temp->nombre, Nombre)!=0)
	temp=temp->sig;

  	if(temp!=NULL)
  	{
    	strcpy(tel_u, tel_urg);
    	strcpy(tel_n, tel);
    	strcpy(consultorio, consul);
    	if(sscanf(tel_u, "%d", &n_u)==1)
      	temp->telefono_urge=n_u;
    	if(sscanf(tel_n, "%d", &n_n)==1)
      	temp->telefono=n_n;
    	if(sscanf(consultorio, "%d", &c)==1)
      	temp->consultorio=c;

    	strcpy(temp->direccion,direccion);
    	strcpy(temp->horario, horario );
    	strcpy(temp->dias,dias);
    	strcpy(temp->estado,estatus);
    	strcpy(temp->especialidad1,espe1);
    	strcpy(temp->especialidad2,espe2);


  	}
  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Cambio guardado con exito");
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);
	gtk_widget_destroy(datos->lista1[11]);
  	gtk_widget_destroy(datos->lista1[9]);
  	gtk_widget_destroy(datos->lista1[10]);
	}

}
/**
 *Mod_Doc1
 *En esta funcion se genera una interfaz gráfica en la que se va a
 *solicitar el nombre del médico que se desea modificar, en caso de que
 *no se llene o que los datos no sean validos, el programa avisara
 *mediante un dialog, una vez que valide que el doctor esta registrado,
 *podra acceder a la modificacion por medio de la funcion Busca_D
 *
 *
 *@author JuanP Gomez
 */

void Mod_Doc1(GtkWidget *menu, gpointer lista)
{
  GtkWidget *vbox,*box,*label,*nom;
  TipoLista* datos=(TipoLista*)lista;

  datos->lista1[11]=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(datos->lista1[11]), "Modificar Doctores");
  gtk_widget_set_size_request (datos->lista1[11], 700, 200);


  vbox = gtk_vbox_new(TRUE,5);


  box = gtk_hbox_new(TRUE,5);



  label=gtk_label_new("Bienvenido a la modificacion de datos de los doctores, para continuar, ingrese el nombre del doctor.");
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(vbox),box,TRUE,TRUE,5);

  box = gtk_hbox_new(TRUE,5);



  label=gtk_label_new("Nombre:");

  datos->lista1[0]= gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(box),datos->lista1[0],TRUE,TRUE,5);


  gtk_box_pack_start(GTK_BOX(vbox),box,TRUE,TRUE,5);



  nom= gtk_button_new_with_label("Aceptar");
  gtk_box_pack_start(GTK_BOX(vbox),nom,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Busca_D),datos);
  gtk_widget_show(nom);

  gtk_signal_connect(GTK_OBJECT(datos->lista1[11]),"destroy",GTK_SIGNAL_FUNC(Destroy),datos->lista1[11]);

  gtk_container_add (GTK_CONTAINER (datos->lista1[11]), vbox);

  gtk_widget_show_all (datos->lista1[11]);
}
/**
 *ayuda
 *La información de cada función principal de doctores, pacientes e
 *historia médica es resumida en una serie de ventanas que se desplegarán
 *cuando el usuario ingrese al menú de ayuda.
 *
 *
 *@author JuanP Gomez
 */

void ayuda()
{
  GtkWidget *assistant;
  guint i;  PageInfo page[10] = {
                  	{ NULL, -1, "Ayuda Medi+",GTK_ASSISTANT_PAGE_INTRO,   TRUE},
                  	{ NULL, -1, "Doctores (registrar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Doctores (consultar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Doctores (modificar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Pacientes (registrar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Pacientes (consultar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Pacientes (modificar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Historia Clínica (registrar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Historia Clínica (consultar).",GTK_ASSISTANT_PAGE_CONTENT, TRUE},
                  	{ NULL, -1, "Historia Clínica (modificar).",GTK_ASSISTANT_PAGE_CONFIRM, TRUE},

                             	};


 /* Create a new assistant widget with no pages. */
  assistant = gtk_assistant_new ();
  gtk_widget_set_size_request (assistant, 450, 300);
  gtk_window_set_title (GTK_WINDOW (assistant), "Ayuda Medi+");

  page[0].widget = gtk_label_new("Bienvenido a la seccion de ayuda de Medi+\n"\
                              	"a continuacion encontrara informacion sobre\n"\
                              	"el uso del programa.");
  page[1].widget = gtk_label_new("Para Medi+, los medicos llevan a cabo un proceso de registro\n"\
              	"en el cual su informacion es recabada y guardada para ofrecer\n"\
              	"la mayor calidad y confianza a nuestros pacientes.\n");
  page[2].widget = gtk_label_new("Una vez guardada la informacion de cada medico, estara¡ disponible\n"\
             	"en la ventana de consulta, la cual permite filtrar por especialidad,\n"\
             	"buscar por nombre o simplemente desplegar toda la lista de doctores.");
  page[3].widget = gtk_label_new("En caso de que sea necesario, la informcaion de los medicos podra\n"\
             	"ser modificada (a excepcion del nombre por temas de seguridad), es\n"\
             	"decir que los doctores estaran monitoreados en caso de cualquier cambio.");
  page[4].widget = gtk_label_new("Para poder ser atendido en nuestra clínica, es\n"\
                              	"necesario que que los pacientes estén registrados\n"\
                              	"en la base de datos, la cual solicitará información\n"\
              	"general del mismo, sin registro no hay atención.");
  page[5].widget = gtk_label_new("Cuando el paciente ingresa a la base de datos,estará disponible\n"\
                              	"su información general, para que así pueda ser consultado por\n"\
                              	"el médico que lo necesite.");
  page[6].widget = gtk_label_new("Se podrá modificar la información general suministrada por el paciente\n"\
              	"para fines de calidad del servicio, sin embargo, el nombre no se podrá\n"\
              	"modificar, para poder monitorear al paciente.\n");
  page[7].widget = gtk_label_new("Cada vez que un paciente entre a consulta, el médico correspondiente\n"\
             	"dará de alta un formato de evaluación del paciente, este contendrá\n"\
             	"las observaciones del doctor, anotaciones e indicaciones.");
  page[8].widget = gtk_label_new("Se le asignará una ficha al paciente por la cual con ayuda de su nombre,\n"\
             	"se podrá buscar cual es el diagnósico del paciente que corresponda\n");
  page[9].widget = gtk_label_new("El archivo clínico se puede modifiar, ya que se debe mantener actualizado\n"\
                              	"de acuerdo a los tratamientos que cada paciente esté llevando.\n"\
                              	"La historia clínica es personal e intransferible.");

	/* Add five pages to the GtkAssistant dialog. */
  for (i = 0; i < 10; i++)
	{
  	page[i].index = gtk_assistant_append_page (GTK_ASSISTANT (assistant), page[i].widget);
  	gtk_assistant_set_page_title(GTK_ASSISTANT (assistant),page[i].widget, page[i].title);
  	gtk_assistant_set_page_type(GTK_ASSISTANT (assistant),page[i].widget, page[i].type);   /* Set the introduction and conclusion pages as complete so they can be 	* incremented or closed. */
  	gtk_assistant_set_page_complete (GTK_ASSISTANT (assistant),page[i].widget, page[i].complete);
	}

  g_signal_connect (G_OBJECT (assistant), "cancel",G_CALLBACK (assistant_cancel), NULL);
  g_signal_connect (G_OBJECT (assistant), "close",G_CALLBACK (assistant_close), NULL);
  gtk_widget_show_all (assistant);

}
void assistant_cancel (GtkAssistant *assistant,gpointer data)
 {
   gtk_widget_destroy (GTK_WIDGET (assistant));
 }/* This function is where you would apply the changes and destroy the assistant. */

void assistant_close (GtkAssistant *assistant,gpointer data)
 {

   gtk_widget_destroy (GTK_WIDGET (assistant));
 }
/**
*Esta función apunta a el notebook de la función cosult_Docy ayudará a cambiar entre las hojas de este
*
*
*@Autor: Enrique Guevara
*/
void switchp(GtkButton *button,GtkNotebook *notebook){
  gint page=gtk_notebook_get_current_page(notebook);
  if (page==0){
	gtk_notebook_set_current_page(notebook,0);
  }
  else if(page==1){
	gtk_notebook_set_current_page(notebook,1);
  }
  else if(page==2){
	gtk_notebook_set_current_page(notebook,2);
  }
}
/**
*Esta función apunta a el notebook de la función cosult_Pac y ayudará a cambiar entre las hojas de este
*
*
*@Autor: Enrique Guevara
*/

void switchp_p(GtkButton *button,GtkNotebook *notebook){
  gint page=gtk_notebook_get_current_page(notebook);
  if (page==0){
	gtk_notebook_set_current_page(notebook,0);
  }
  else if(page==1){
	gtk_notebook_set_current_page(notebook,1);
  }
}
/**
*setup_tree_v
*Esta función crear el render, de la treeview de los doctores
*creando las columnas que tendrá esta vista usando los valores del enum, para seguir un orden de las columnas
*para después agregarlas a la tree view
*
*@Autor: Enrique Guevara
*
*/

void steup_tree_v(GtkWidget* treeview){
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *colum;
  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Nombre",renderer,"text",NOMBRE,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Especialidad 1",renderer,"text",ESP_1,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Especialidad 2",renderer,"text",ESP_2,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("ESTADO",renderer,"text",ESTADO,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Telefono de urgencias",renderer,"text",TEL_URG,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Direccion",renderer,"text",DIRECCION,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Telefono",renderer,"text",TEL,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Consultorio",renderer,"text",CONSULTORIO,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Dias",renderer,"text",DIAS,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Horario",renderer,"text",HORARIO,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);
}
/**
*
*Esta función creará un ventana con en treeview donde recibirá la lista en un temporal se apuntará a la lista de los doctores, para filtrarlos por especialidad, y irlos agregando a la tree view
*se convertirá en mayúsculas los nombres y las especialidades
*en caso de no encontrar nada se le avisará al usuario.
*
*@Autor: Enrique Guevara
*/

void busca1(GtkWidget *button1,gpointer lista){
   GtkWidget *window,*treeview,*scrolled_win,*dialog;
  GtkListStore *store;
  GtkTreeIter iter;
  const gchar *Nombre;
  gint i=0;
  TipoDoctor *temp;
  TipoLista* datos= (TipoLista*)lista;
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request(window,850,500);
  gtk_window_set_title(GTK_WINDOW(window),"Doctores");
  Nombre=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  treeview=gtk_tree_view_new();
  temp=datos->Doc01;
  steup_tree_v(treeview);
  store=gtk_list_store_new(COLUM,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,
          	G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT);
  while(temp!=NULL){
  if(strcmp(Nombre,temp->especialidad1)==0 || strcmp(Nombre,temp->especialidad2)==0){
	gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,NOMBRE,temp->nombre,ESP_1,temp->especialidad1,ESP_2,temp->especialidad2,ESTADO,temp->estado,TEL_URG,temp->telefono_urge,DIRECCION,temp->direccion,TEL,temp->telefono,CONSULTORIO,temp->consultorio,DIAS,temp->dias,HORARIO,temp->horario,-1);
	++i;
	}
	temp=temp->sig;
  }
  if(i>0){
  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(store));
  g_object_unref(store);

  scrolled_win = gtk_scrolled_window_new (NULL, NULL);  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add (GTK_CONTAINER (scrolled_win),treeview);
  gtk_container_add (GTK_CONTAINER (window), scrolled_win);
  gtk_widget_show_all (window);


  }
  else{
 	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "No se encontreron resultados ");
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

  }
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
}

/**
*
*Esta función creará un ventana con en treeview donde recibirá la lista en un temporal se apuntará a la lista de los doctores, para filtrarlos por nombre, y irlos agregando a la tree view
*se convertirá en mayúsculas los nombres y las especialidades
*en caso de no encontrar nada se le avisará al usuario.
*@Autor: Enrique Guevara

*/

void busca2(GtkWidget *button1,gpointer lista){
   GtkWidget *window,*treeview,*scrolled_win,*dialog;

  GtkListStore *store;
  GtkTreeIter iter;
  const gchar *Nombre;
  char nomre[40],nomre1[40];
  int p=0 , i;
  TipoDoctor *temp;
  TipoLista* datos= (TipoLista*)lista;
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request(window,850,500);
  gtk_window_set_title(GTK_WINDOW(window),"Doctores");

  treeview=gtk_tree_view_new();

  temp=datos->Doc01;
  steup_tree_v(treeview);
  store=gtk_list_store_new(COLUM,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,
          	G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT);


  Nombre=gtk_entry_get_text(GTK_ENTRY(datos->lista1[2]));
  if(strcmp(Nombre, "\0")==0)
    {
      dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor rellena el dato del nombre del doctor ");
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);



    }
  else
    {
      strcpy(nomre1,Nombre);
      while(temp!=NULL)
	{

	  strcpy(nomre,temp->nombre);
	  for(i=0;i<=strlen(nomre)-1;i++)
	    {
	      if(nomre[i]>='a' && nomre[i]<='z')
		nomre[i]=nomre[i]-'a'+'A';
	       
	    }
	  for(i=0;i<=strlen(nomre1)-1;i++)
	    {
	      if(nomre1[i]>='a' && nomre1[i]<='z')
		nomre1[i]=nomre1[i]-'a'+'A';
	    }
	  
	  
	  if(strcmp(nomre,nomre1)==0 )
	    {
	      gtk_list_store_append(store,&iter);
	      gtk_list_store_set(store,&iter,NOMBRE,temp->nombre,ESP_1,temp->especialidad1,ESP_2,temp->especialidad2,ESTADO,temp->estado,TEL_URG,temp->telefono_urge,DIRECCION,temp->direccion,TEL,temp->telefono,CONSULTORIO,temp->consultorio,DIAS,temp->dias,HORARIO,temp->horario,-1);
	      ++p;
	    }
	  temp=temp->sig;
	}
      if(p>0)
	{
	  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(store));
	  g_object_unref(store);

	  scrolled_win = gtk_scrolled_window_new (NULL, NULL);  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	  gtk_container_add (GTK_CONTAINER (scrolled_win),treeview);
	  gtk_container_add (GTK_CONTAINER (window), scrolled_win);
	  gtk_widget_show_all (window);


	}
      else
	{
	  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "No se encontreron resultados ");
	  gtk_dialog_run(GTK_DIALOG(dialog));
	  gtk_widget_destroy(dialog);

	}
      gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);





    }


}
/**
*
*Esta función creará un ventana con en treeview donde recibirá la lista en un temporal se apuntará a la lista de los usuarios, para filtrarlos por nombre, y irlos agregando a la tree view
*se convertirá en mayúsculas los nombres y las especialidades
*en caso de no encontrar nada se le avisará al usuario.
*
*@Autor: Enrique Guevara
*/

void buscap(GtkWidget *button1,gpointer lista)

{
   GtkWidget *window,*treeview,*scrolled_win,*dialog;
  GtkListStore *store;
  GtkTreeIter iter;
  char nom[50];
  const gchar *Nombre;
  gint i=0;
  TipoPaciente *temp;
  TipoLista* datos= (TipoLista*)lista;
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request(window,850,500);
  gtk_window_set_title(GTK_WINDOW(window),"Doctores");
 
  treeview=gtk_tree_view_new();
  temp=datos->Pac01;
  steup_tree_v_p(treeview);
  store=gtk_list_store_new(COLUM,G_TYPE_STRING,G_TYPE_STRING,
			   G_TYPE_INT,
			   G_TYPE_CHAR,G_TYPE_STRING,
			   G_TYPE_INT,G_TYPE_FLOAT,
			   G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

  Nombre=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  if(strcmp(Nombre, "\0")==0)
    {
      dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Porfavor ingresa el nombre del paciente ");
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
      
      
    }
  else
    {
      strcpy(nom, Nombre);
      for(i=0;i<=strlen(nom)-1;i++)
	{
	  if(nom[i]>='a' && nom[i]<='z')
	    nom[i]=nom[i]-'a'+'A';
	}

      while(temp!=NULL)
	{
	  if(strcmp(nom,temp->nombre)==0 )
	    {
	      gtk_list_store_append(store,&iter);
	      gtk_list_store_set(store,&iter,NOMBREP,temp->nombre,DIRECCIONP,temp->direccion,TELEFONOP,temp->telefono,SEXOP,temp->sexo,FECHAP,temp->fecha,EDADP,temp->edad,ESTATURAP,temp->estatura,ALERGIAP,temp->alergias,SANGREP,temp->sangre,PADECIMIENTOSP,temp->padecimientos,-1);
	      ++i;
	    }
	  temp=temp->sig;
	}
      if(i>0)
	{
	  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(store));
	  g_object_unref(store);
	  
	  scrolled_win = gtk_scrolled_window_new (NULL, NULL);  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	  gtk_container_add (GTK_CONTAINER (scrolled_win),treeview);
	  gtk_container_add (GTK_CONTAINER (window), scrolled_win);
	  gtk_widget_show_all (window);
	  
	  
	}
      else
	{
	  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "No se encontreron resultados ");
	  gtk_dialog_run(GTK_DIALOG(dialog));
	  gtk_widget_destroy(dialog);
	  
	}
      gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
    }
}

/**
 *Mod_Pac
 *Despliega una ventana en la cual se debe ingresar el nombre del paciente
 *que se desea modificar, se verificará que el entry no esté vacío y que el
 *paciente esté registrado en el programa, una vez que sea verificado, va a
 *acceder a la ventana de modificación mediante la función Busca_P
 *
 *
 *@author JuanP Gomez
 */
void Mod_Pac(GtkWidget *menu, gpointer lista)
{
  GtkWidget *vbox,*box,*label,*nom;
  TipoLista* datos=(TipoLista*)lista;

  datos->lista1[11]=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(datos->lista1[11]), "Modificar Pacientes");
  gtk_widget_set_size_request (datos->lista1[11], 700, 200);


  vbox = gtk_vbox_new(TRUE,5);


  box = gtk_hbox_new(TRUE,5);



  label=gtk_label_new("Bienvenido a la modificacion de datos de los pacientes, para continuar,\ningrese el nombre del paciente a modificar.");
  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(vbox),box,TRUE,TRUE,5);

  box = gtk_hbox_new(TRUE,5);



  label=gtk_label_new("Nombre:");

  datos->lista1[0]= gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(box),datos->lista1[0],TRUE,TRUE,5);


  gtk_box_pack_start(GTK_BOX(vbox),box,TRUE,TRUE,5);



  nom= gtk_button_new_with_label("Aceptar");
  gtk_box_pack_start(GTK_BOX(vbox),nom,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Busca_P),datos);
  gtk_widget_show(nom);

  gtk_signal_connect(GTK_OBJECT(datos->lista1[11]),"destroy",GTK_SIGNAL_FUNC(Destroy),datos->lista1[11]);

  gtk_container_add (GTK_CONTAINER (datos->lista1[11]), vbox);
  gtk_widget_show_all(datos->lista1[11]);
}
/**
 *Busca_P
 *Una vez ya validado el nombre del paciente a modificar, la función va a
 *se va a encargar de recorrer la lista de pacientes hasta encontar alguna
 *coincidencia, cuando lo encuentre, desplegará una ventana en la que los
 *datos podrán ser reescritos, en caso de que la función no encuentre al
 *paciente, regresará un dialog.
 *
 *
 *@author JuanP Gomez
 */

void Busca_P(GtkWidget *menu, gpointer lista)
{
  GtkWidget *window, *label, *vbox, *nom, *dialog,*box,*vbox1,*vbox2,*box1;
  GtkAdjustment *float_pt;
  TipoPaciente *temp;
  char band[40], Nombre[50], tel[20], edad[20], sex[10];
  const gchar* Nombre_P;
  TipoLista *datos= (TipoLista*)lista;

  int i;
  temp=datos->Pac01;
  strcpy(band, "\0");

  Nombre_P=gtk_entry_get_text(GTK_ENTRY(datos->lista1[0]));
  if(strcmp(Nombre_P,"\0")==0)
	strcpy(band, "Nombre del Paciente");



  if(strcmp(band, "\0")!=0)
	{
  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Por favor ingresa el %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);
	}
  else
  {

	strcpy(Nombre,Nombre_P);
	for(i=0;i<=strlen(Nombre_P)-1;i++)
  	{
    if(Nombre[i]>='a' && Nombre[i]<='z')
      Nombre[i]=Nombre[i]-'a'+'A';

  	}


  while(temp!=NULL&&strcmp(Nombre, temp->nombre)!=0)
	temp=temp->sig;


  if(temp!=NULL)
	{

  	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_title (GTK_WINDOW (window), "Modificacion de Pacientes");
  	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  	label = gtk_label_new ("Datos del Paciente:");

  	vbox = gtk_vbox_new (FALSE, 5);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox), label);

  	label = gtk_label_new ("Nombre:");
  	nom = gtk_label_new (Nombre);
  	datos->lista1[0] = nom;

  	box=gtk_vbox_new(FALSE, 5);

  	vbox1 = gtk_hbox_new (FALSE, 5);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[0]);
  	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

  	vbox1 = gtk_hbox_new (FALSE, 5);

  	label = gtk_label_new ("Dirección:");
  	datos->lista1[1] = gtk_entry_new ();
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[1]),temp->direccion);
  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[1]), TRUE);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[1]);
  	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

  	sprintf(tel,"%d",temp->telefono);

  	label = gtk_label_new ("Teléfono:");
  	datos->lista1[2] = gtk_entry_new ();
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[2]),tel);
  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[2]), TRUE);

  	vbox1 = gtk_hbox_new (FALSE, 5);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[2]);
  	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);

  	label = gtk_label_new ("Alergias:");
  	datos->lista1[3] = gtk_entry_new ();
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[3]),temp->alergias);
  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[3]), TRUE);

  	vbox1 = gtk_hbox_new (FALSE, 5);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[3]);
  	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


  	label = gtk_label_new ("Padecimientos crónicos:");
  	datos->lista1[4] = gtk_entry_new ();
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[4]),temp->padecimientos);
  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[4]), TRUE);

  	vbox1 = gtk_hbox_new (FALSE, 5);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[4]);
  	gtk_box_pack_start_defaults (GTK_BOX (box), vbox1);


  	vbox2 = gtk_vbox_new (FALSE, 5);
  	label = gtk_label_new ("Sexo:");
  	datos->lista1[5] = gtk_entry_new ();
	sprintf(sex, "%c",temp->sexo);
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[5]),sex);

  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[5]), TRUE);

  	vbox1=gtk_hbox_new(TRUE,5);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[5]);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

  	label = gtk_label_new ("Fecha de nacimiento:");
  	datos->lista1[6] = gtk_entry_new ();
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[6]), temp->fecha);
  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[6]), TRUE);

  	vbox1=gtk_hbox_new(FALSE,5);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[6]);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);


  	sprintf(edad,"%d",temp->edad);

  	label = gtk_label_new ("Edad:");
  	datos->lista1[7] = gtk_entry_new ();
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[7]),edad);
  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[7]), TRUE);
  	//gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

  	vbox1=gtk_hbox_new(FALSE,5);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[7]);

   	label = gtk_label_new ("Estatura:");

  	float_pt = GTK_ADJUSTMENT (gtk_adjustment_new (0.5, 0.0, 2.0, 0.01, 0.5, 0));
  	datos->lista1[8] = gtk_spin_button_new (float_pt, 0.01, 2);
  	///////como sacar el valor del spin

  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[8]);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);

  	label = gtk_label_new ("Sangre:");
  	datos->lista1[9] = gtk_entry_new ();
  	gtk_entry_set_text(GTK_ENTRY(datos->lista1[9]),temp->sangre);
  	gtk_entry_set_visibility (GTK_ENTRY (datos->lista1[9]), TRUE);


  	vbox1=gtk_hbox_new(FALSE,5);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), label);
  	gtk_box_pack_start_defaults (GTK_BOX (vbox1), datos->lista1[9]);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox2), vbox1);


  	datos->lista1[10]=window;

  	nom= gtk_button_new_with_label("Aceptar");
  	gtk_box_pack_start(GTK_BOX(vbox2),nom,FALSE,TRUE,0);
  	gtk_signal_connect(GTK_OBJECT(nom),"clicked",GTK_SIGNAL_FUNC(Cambiar_P),datos);
  	gtk_widget_show(nom);

  	box1=gtk_hbox_new(TRUE,5);
  	gtk_box_pack_start_defaults (GTK_BOX (box1), box);
  	gtk_box_pack_start_defaults (GTK_BOX (box1), vbox2);

  	gtk_box_pack_start_defaults (GTK_BOX (vbox), box1);

  	gtk_container_add (GTK_CONTAINER (window), vbox);

  	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
  	gtk_widget_show_all (window);



	}else
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El paciente no esta dado de alta");
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}

  }

}
/**
 *Cambiar_P
 *Cuando el usuario haya registrado los nuevos datos, esta función
 *se encargará de escribir sobre la lista dinámica para guardar los cambios,
 *los cambios no se podrán guardar si la información no se ha ingresado por
 *completo.
 *
 *
 *@author JuanP Gomez
 */

void Cambiar_P(GtkWidget *menu, gpointer lista)
{
  char band[35], Nombre[20];

  const gchar* Nombre_P, *direccion, *tel, *sexo, *fecha,*edad,*estatura,  *alergias, *sangre, *padecimientos;
  TipoPaciente *temp;
  int i,ntel, ed,estat;
  GtkWidget *dialog;
  char se;
  TipoLista *datos= (TipoLista*)lista;

  temp=datos->Pac01;


  strcpy(band, "\0");

  Nombre_P=gtk_label_get_text(GTK_LABEL(datos->lista1[0]));
  /*if(strcmp(Nombre_D,"\0")==0)
	strcpy(band, "Nombre del paciente");*/

  direccion=gtk_entry_get_text(GTK_ENTRY(datos->lista1[1]));
  if(strcmp(direccion,"\0")==0)
  strcpy(band, "Direccion");


  tel=gtk_entry_get_text(GTK_ENTRY(datos->lista1[2]));
  if(strcmp(tel ,"\0")==0)
  strcpy(band, "Telefono");


  sexo=gtk_entry_get_text(GTK_ENTRY(datos->lista1[5]));
  if(strcmp(sexo,"\0")==0)
  strcpy(band, "Sexo");


  fecha=gtk_entry_get_text(GTK_ENTRY(datos->lista1[6]));
  if(strcmp(fecha,"\0")==0)
  strcpy(band, "Fecha de nacimiento");

  edad=gtk_entry_get_text(GTK_ENTRY(datos->lista1[7]));
  if(strcmp(edad,"\0")==0)
  strcpy(band, "Edad ");

  estatura=gtk_entry_get_text(GTK_ENTRY(datos->lista1[8]));
  if(strcmp(estatura,"\0")==0)
  strcpy(band, "Estatura");

  alergias=gtk_entry_get_text(GTK_ENTRY(datos->lista1[3]));
  if(strcmp(alergias,"\0")==0)
  strcpy(band, "Alergias");

  sangre=gtk_entry_get_text(GTK_ENTRY(datos->lista1[9]));
  if(strcmp(sangre,"\0")==0)
  strcpy(band, "Tipo de sangre");

  padecimientos=gtk_entry_get_text(GTK_ENTRY(datos->lista1[4]));
  if(strcmp(padecimientos,"\0")==0)
  strcpy(band, "Padecimientos crónicos");






  strcpy(Nombre,Nombre_P);
  for(i=0;i<=strlen(Nombre)-1;i++)
	{
  	if(Nombre[i]>='a' && Nombre[i]<='z')
  Nombre[i]=Nombre[i]-'a'+'A';

	}


  if(strcmp(band, "\0")!=0)
	{

  	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Falta ingresar el dato de %s", band);
  	gtk_dialog_run(GTK_DIALOG(dialog));
  	gtk_widget_destroy(dialog);

	}
  else
	{
  	while(temp!=NULL&&strcmp(temp->nombre, Nombre)!=0)
  temp=temp->sig;

	if(temp!=NULL)
	{
	  //	strcpy(telp, tel);
	  //strcpy(edadp, edad);
	  //strcpy(estaturap, estatura);
  	sscanf(tel,"%d", &ntel);
    	temp->telefono=ntel;
  	sscanf(edad,"%d", &ed);
    	temp->edad=ed;
  	sscanf(estatura,"%d", &estat);
    	temp->estatura=estat;

  	strcpy(temp->direccion,direccion);
	sscanf(sexo, "%c", &se);
  	temp->sexo=se;
  	strcpy(temp->fecha,fecha);
  	strcpy(temp->alergias,alergias);
  	strcpy(temp->sangre,sangre);
  	strcpy(temp->padecimientos,padecimientos);


	}
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Cambio guardado con exito");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	gtk_widget_destroy(datos->lista1[11]);
	//gtk_widget_destroy(datos->lista1[9]);
	gtk_widget_destroy(datos->lista1[10]);
	}
}
/**
*
*Esta función crear el render, de la treeview de los pacientes,
*creando las columnas que tendrá esta vista usando los valores del enum, para seguir un orden de las columnas
*para después agregarlas a la tree view
*
*@Autor: Enrique Guevara
*
*/

void steup_tree_v_p(GtkWidget* treeview)
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *colum;
  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Nombre",renderer,"text",NOMBRE,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Direccion",renderer,"text",DIRECCIONP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Telefono",renderer,"text",TELEFONOP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Sexo",renderer,"text",SEXOP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Fecha de nacimiento",renderer,"text",FECHAP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

	renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Edad",renderer,"text",EDADP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

	renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Estatura",renderer,"text",ESTATURAP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Alergias",renderer,"text",ALERGIAP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Tipo de sangre",renderer,"text",SANGREP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

  renderer=gtk_cell_renderer_text_new();
  colum=gtk_tree_view_column_new_with_attributes("Padecimientos",renderer,"text",PADECIMIENTOSP,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),colum);

}
/**
*
*Esta función crear una ventana que contenga un notebook donde se mostrara, dos opciones para consultar los pacientes
*el primero mostrará la treeview con todos los pacientes, en la segunda aparecerá una entri box, un label y un botón para buscar
*los nombres de los pacientes, donde se creará una ventana con cun un filtro de los nombres,se enviará la lista a una función, en caso de no encontrar nada o no introducir nada se le notificará al usuario

*
*@Autor: Enrique Guevara
*
*/

void consult_Pac(GtkWidget *menu, gpointer lista)
{
  GtkWidget *window,*notebook, *treeview,*scrolled_win, *box, *viewport,*hbox1,*hbox2,*vbox3,*dialog;
  GtkWidget *label,*label1,*label2,*cbox,*button1;
  GtkListStore *store;
  GtkTreeIter iter;
  GtkAdjustment *horizontal, *vertical;
  TipoPaciente *temp;
  TipoLista* datos= (TipoLista*)lista;
  char nomre[50];
  int i;
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request(window,850,500);
  gtk_window_set_title(GTK_WINDOW(window),"Pacientes");
  box = gtk_vbox_new(TRUE,5);
  hbox2 = gtk_hbox_new(TRUE,5);
  hbox1 = gtk_hbox_new(TRUE,5);
  vbox3=gtk_vbox_new(TRUE,5);
  
  if(datos->Pac01!=NULL){
    temp=datos->Pac01;
    
    treeview=gtk_tree_view_new();
    steup_tree_v_p(treeview);
    store=gtk_list_store_new(COLUMP,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_CHAR
			     ,G_TYPE_STRING,G_TYPE_INT,G_TYPE_FLOAT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    while(temp!=NULL){
      
      strcpy(nomre,temp->nombre);
      if(nomre!='\0'){
  	for(i=0;i<=strlen(temp->nombre)-1;++i){
	  if(nomre[i]>='a' && nomre[i]<='z'){
	    nomre[i]=nomre[i]-'a'+'A';
	  }
	}
	
      }
	gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,NOMBREP,nomre,DIRECCIONP,temp->direccion,TELEFONOP,temp->telefono,SEXOP,temp->sexo,FECHAP,temp->fecha,EDADP,temp->edad,ESTATURAP,temp->estatura,ALERGIAP,temp->alergias,SANGREP,temp->sangre,PADECIMIENTOSP,temp->padecimientos,-1);
	temp=temp->sig;
    }
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(store));
    g_object_unref(store);
    scrolled_win=gtk_scrolled_window_new(NULL,NULL);
    horizontal = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (scrolled_win));
    vertical = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (scrolled_win));
    viewport = gtk_viewport_new (horizontal, vertical);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(viewport),treeview);
    gtk_box_pack_start(GTK_BOX(box),viewport,FALSE,FALSE,0);
    //Fin de note 1
    //Inicio de note 2
    label=gtk_label_new("Nombre");
    cbox= gtk_entry_new();
    datos->lista1[0] = cbox;
    button1=gtk_button_new_with_label("Busca");
    gtk_box_pack_start(GTK_BOX(hbox1),label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox1),cbox,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox1),button1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox3),hbox1,FALSE,FALSE,0);
    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(buscap),datos);
    
    //Fin de note 2
    
    notebook=gtk_notebook_new();
    label1=gtk_label_new("Global");
    label2=gtk_label_new("Nombre");
    
    g_signal_connect(G_OBJECT(label1),"clicked",G_CALLBACK(switchp),(gpointer) notebook);
    
    
    g_signal_connect(G_OBJECT(label2),"clicked",G_CALLBACK(switchp),(gpointer) notebook);
    
    
    gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),box,label1);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),vbox3,label2);
    
    
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_BOTTOM);
    
    gtk_container_add(GTK_CONTAINER(window),notebook);
    gtk_widget_show_all(window);
  }else{
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "No hay doctores aun");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_signal_connect(GTK_OBJECT(dialog),"destroy",GTK_SIGNAL_FUNC(Destroy),window);
    
  }
}
