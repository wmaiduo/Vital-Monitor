/**
 * @author Pratishtha Sharma
 * @author Zain Khan
 * @brief Main program to run the vitals sensor from & output a monitor display using Gtk GUI
*/

#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <istream>
#include <gtk/gtk.h>

#include "Monitor_Class.h"
#include "Sensor_Class.h"
#include "Blood_Pressure_Alert.h"
#include "Body_Temp_Alert.h"
#include "Pulse_Rate_Alert.h"
#include "Respiration_Rate_Alert.h"

using namespace std;

//Function Prototypes for GUI Handler Functions.
void handler1(GtkButton *button, gpointer *user_data);
void handler2(GtkButton *button, gpointer *user_data);
void handler3(GtkButton *button, gpointer *user_data);
void handler4(GtkButton *button, gpointer *user_data);
void alert_dialog(GtkWidget *wid, gpointer *win);
void end_program(GtkWidget *wid, gpointer ptr);

GtkWidget *win; //Global Variable to be accessed by all Gtk Widgets.
vector<float> data_values; //Global variable to be accessed by all handler functions.

/**
 * @brief Main function to run the vitals sensor from & output a monitor display
*/
int main(int argc, char *argv[])
{
    Monitor_Class monitor;
    Sensor_Class sensor;
	
    // Use the monitor class to get user input for which vitals they wish to test		
    vector<string> selected_vitals = monitor.displayMessage();
	
    // Start the sensors for whichever vitals were selected by the user
    for(int i = 0; i < selected_vitals.size(); i++){sensor.testVitals(selected_vitals[i]);}
	
    // Generate a random number to select a random data values from the generated sensor data	
    int random_measurment;
    srand(time(0));
    random_measurment = rand() % 1000 + 61;

    for(int j = 0; j < 1000; j++)
    {
		if (j == random_measurment)
        	{
			sensor.stopBP(); //stop BP sensor after random_measurement amount of seconds
			sensor.stopBT(); //stop BT sensor after random_measurement amount of seconds
			sensor.stopPR();//stop PR sensor after random_measurement amount of seconds
			sensor.stopRR();//stop RR sensor after random_measurement amount of seconds
			
			break; //if it reaches limit then break
		}
	// Set the data values vector with the random values generated    
        data_values = sensor.getValue();
    }

    // -------------------------------------------------------------------------------------- //
    //                                  GUI INTERFACE BEGINS

    gtk_init(&argc, &argv); //Initialize the Gtk GUI

    //Create Gtk Widgets (Elements)
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *box = gtk_vbox_new(FALSE, 5);
    GtkWidget *hbox1 = gtk_hbox_new(TRUE, 5);
    GtkWidget *hbox2 = gtk_hbox_new(TRUE, 5);
    GtkWidget *hbox3 = gtk_hbox_new(TRUE, 5);
    GtkWidget *hbox4 = gtk_hbox_new(TRUE, 5);

    GtkWidget *lbl = gtk_label_new("Project Vitality");
    GtkWidget *image = gtk_image_new_from_file("doctor.png");
    GtkWidget *lbl_instr = gtk_label_new("Click the vital you'd like to show (Unselected vitals are left blank)...");

    //Create buttons for GUI User Interaction
    GtkWidget *btn1 = gtk_button_new_with_label("Blood Pressure");
    GtkWidget *btn2 = gtk_button_new_with_label("Body Temperature");
    GtkWidget *btn3 = gtk_button_new_with_label("Pulse Rate");
    GtkWidget *btn4 = gtk_button_new_with_label("Respiration Rate");

    GtkWidget *lbl1 = gtk_label_new(" - ");
    GtkWidget *lbl2 = gtk_label_new(" - ");
    GtkWidget *lbl3 = gtk_label_new(" - ");
    GtkWidget *lbl4 = gtk_label_new(" - ");

    gtk_box_pack_start(GTK_BOX(hbox1), btn1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), lbl1, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(hbox2), btn2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), lbl2, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox3), btn3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox3), lbl3, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox4), btn4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox4), lbl4, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), lbl_instr, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), hbox1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), hbox2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), hbox3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), hbox4, TRUE, TRUE, 0);

    // Create and Collect Signals for Gtk Interaction
    g_signal_connect(btn1, "clicked", G_CALLBACK(handler1), lbl1);
    g_signal_connect(btn2, "clicked", G_CALLBACK(handler2), lbl2);
    g_signal_connect(btn3, "clicked", G_CALLBACK(handler3), lbl3);
    g_signal_connect(btn4, "clicked", G_CALLBACK(handler4), lbl4);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL); //Close Program when you close window.


    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    gtk_main(); // Loop Gtk GUI Program


    return 0;
}

/**
 * @brief Handler function for when Button 1 (Blood Pressure) is clicked. Reacts to signal and changes Gtk GUI accordingly.
 * @param button pointer to refer to Button 1 Gtk Object and user_data to pass additional Gtk Widget (Label 1)
*/
void handler1(GtkButton *button, gpointer *user_data){

    char output[50] = " ";

    Blood_Pressure_Alert bp_alert(data_values);
    bp_alert.checkValue();

    float sysBloodPressure = bp_alert.get_systolicBloodPressure();
    float diaBloodPressure = bp_alert.get_diastolicBloodPressure();
    

    //Alert Message
    if(bp_alert.get_isDanger()){
        
        std::string inputStr = bp_alert.get_riskLevel();
        int size = inputStr.length();
        char riskAlert[size + 1];
        strcpy(riskAlert, inputStr.c_str());

        GtkWidget *dlg = gtk_message_dialog_new(GTK_WINDOW(win),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        riskAlert);

        gtk_window_set_title(GTK_WINDOW(dlg), "Alert!");
        gtk_dialog_run(GTK_DIALOG(dlg));
        gtk_widget_destroy(dlg);
    }

    if(sysBloodPressure != -1){ sprintf(output, "%.2f mmHg / %.2f mmHg", sysBloodPressure, diaBloodPressure);}
    gtk_label_set_text((GTK_LABEL (user_data)), output);
}

/**
 * @brief Handler function for when Button 2 (Body Temperature) is clicked. Reacts to signal and changes Gtk GUI accordingly.
 * @param button pointer to refer to Button 2 Gtk Object and user_data to pass additional Gtk Widget (Label 2)
*/
void handler2(GtkButton *button, gpointer *user_data){

    char output[50] = " ";

    Body_Temp_Alert bt_alert(data_values);
    bt_alert.checkValue();

    float bodyTemp = bt_alert.get_bodyTemperature();

    if(bt_alert.get_isDanger()){
        
        std::string inputStr = bt_alert.get_riskLevel();
        int size = inputStr.length();
        char riskAlert[size + 1];
        strcpy(riskAlert, inputStr.c_str());

        GtkWidget *dlg = gtk_message_dialog_new(GTK_WINDOW(win),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        riskAlert);

        gtk_window_set_title(GTK_WINDOW(dlg), "Alert!");
        gtk_dialog_run(GTK_DIALOG(dlg));
        gtk_widget_destroy(dlg);
    }

    if(bodyTemp != -1){ sprintf(output, "%.2f Celsius", bodyTemp);}
    gtk_label_set_text((GTK_LABEL (user_data)), output);

}


/**
 * @brief Handler function for when Button 3 (Pulse Rate) is clicked. Reacts to signal and changes Gtk GUI accordingly.
 * @param button pointer to refer to Button 3 Gtk Object and user_data to pass additional Gtk Widget (Label 3)
*/
void handler3(GtkButton *button, gpointer *user_data){
    
    char output[50] = " ";

    Pulse_Rate_Alert pr_alert(data_values);
    pr_alert.checkValue();

    float pulseRate = pr_alert.get_pulseRate();

    if(pr_alert.get_isDanger()){

        std::string inputStr = pr_alert.get_riskLevel();
        int size = inputStr.length();
        char riskAlert[size + 1];
        strcpy(riskAlert, inputStr.c_str());

        GtkWidget *dlg = gtk_message_dialog_new(GTK_WINDOW(win),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        riskAlert);
    
        gtk_window_set_title(GTK_WINDOW(dlg), "Alert!");
        gtk_dialog_run(GTK_DIALOG(dlg));
        gtk_widget_destroy(dlg);
    }

    if(pulseRate != -1){sprintf(output, "%.2f BPM", pulseRate);}
    
    gtk_label_set_text((GTK_LABEL (user_data)), output);

}


/**
 * @brief Handler function for when Button 4 (Respiration Rate) is clicked. Reacts to signal and changes Gtk GUI accordingly.
 * @param button pointer to refer to Button 4 Gtk Object and user_data to pass additional Gtk Widget (Label 4)
*/
void handler4(GtkButton *button, gpointer *user_data){
    char output[50] = " ";

    Respiration_Rate_Alert rr_alert(data_values);
    rr_alert.checkValue();

    float RespRate = rr_alert.get_respirationRate();

    if(rr_alert.get_isDanger()){

        std::string inputStr = rr_alert.get_riskLevel();
        int size = inputStr.length();
        char riskAlert[size + 1];
        strcpy(riskAlert, inputStr.c_str());

        GtkWidget *dlg = gtk_message_dialog_new(GTK_WINDOW(win),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        riskAlert);
    
        gtk_window_set_title(GTK_WINDOW(dlg), "Alert!");
        gtk_dialog_run(GTK_DIALOG(dlg));
        gtk_widget_destroy(dlg);
    }

    if(RespRate != -1){sprintf(output, "%.2f BPM", RespRate);}
    gtk_label_set_text((GTK_LABEL (user_data)), output);
}

/**
 * @brief Function to end program and Gtk GUI Loop
 * @param 'wid': Gtk Window element to close, 'ptr': Default param for Gtk GUI.
*/
void end_program(GtkWidget *wid, gpointer ptr){
    gtk_main_quit();
}
