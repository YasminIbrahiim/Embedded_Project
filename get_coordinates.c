double GPS_cordinates(double *lat_do, double *long_do)
{


    char frst_ch = '0', dumm_var = '0';   


     
    char lat[18] = "0", longt[10] = "0";
    
 while(1){
    while ((UART2_FR_R & 0x10) != 0)
    {}
    frst_ch = UART2_DR_R&0xFF;

    
    if(frst_ch == '$')
    {
        
        char sec_ch = '0', thr_ch = '0', frth_ch = '0', ffth_ch = '0', sx_ch = '0';



        while ((UART2_FR_R & 0x10) != 0)
        {}
        sec_ch = UART2_DR_R&0xFF;

        while ((UART2_FR_R & 0x10) != 0)
        {}
        thr_ch = UART2_DR_R&0xFF;

        while ((UART2_FR_R & 0x10) != 0)
        {}
        frth_ch = UART2_DR_R&0xFF;

        while ((UART2_FR_R & 0x10) != 0)
        {}
        ffth_ch = UART2_DR_R&0xFF;

        while ((UART2_FR_R & 0x10) != 0)
        {}
        sx_ch = UART2_DR_R&0xFF;


    
        if(sec_ch == 'G' && thr_ch == 'P' && frth_ch == 'G' && ffth_ch == 'L' && sx_ch == 'L')
        {

           



            

            int comm = 0;                       
            bool end = true ;              
           
            while(end == true)
                {
                    while ((UART2_FR_R & 0x10) != 0)
                    {}
                    dumm_var = UART2_DR_R&0xFF;


                    if(comm == 1)       
                    {
                        if(dumm_var != ',') 
                        {
                            strncat(lat, &dumm_var, 1);
                            *lat_do = atof(lat);
                            
                            
                        }
                    }

                    if(comm == 3)           
                    {
                        if(dumm_var != ',')  
                        {
                            strncat(longt, &dumm_var, 1);
                            *long_do =atof( longt);
                           
                        }
                    }

                   
                    if(dumm_var == ',')
                    {
                        comm++ ;
                    }
                    if(dumm_var == '*')
                    {
                        end = false ;
                        goto main;
                    }
            }

        }
    }}
 main:
    return 0;
}