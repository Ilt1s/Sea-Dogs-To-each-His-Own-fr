#include "SD\TEXT\DIALOGS\Common_citizen.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("J'ai entendu dire, "+ GetSexPhrase("monsieur","madame") + DLG_TEXT_BASE[3], DLG_TEXT_BASE[4]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[5], DLG_TEXT_BASE[6]);
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[7], DLG_TEXT_BASE[8]);
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple(DLG_TEXT_BASE[9], DLG_TEXT_BASE[10]);
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple(DLG_TEXT_BASE[11], DLG_TEXT_BASE[12]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[13], DLG_TEXT_BASE[14]);
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[15], DLG_TEXT_BASE[16]);
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple(DLG_TEXT_BASE[17], DLG_TEXT_BASE[18]);
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20], DLG_TEXT_BASE[21])
                                +GetFullName(npchar)
                                +LinkRandPhrase(DLG_TEXT_BASE[22], DLG_TEXT_BASE[23]
                                +NPCharSexPhrase(NPChar, DLG_TEXT_BASE[24], DLG_TEXT_BASE[25])
                                +DLG_TEXT_BASE[26], DLG_TEXT_BASE[27]),

        		                LinkRandPhrase(DLG_TEXT_BASE[28] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[29] + GetFullName(npchar) + DLG_TEXT_BASE[30],
                                 DLG_TEXT_BASE[31] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[32] + GetFullName(npchar) + DLG_TEXT_BASE[33],
                                 DLG_TEXT_BASE[34] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[35] + GetFullName(npchar) + DLG_TEXT_BASE[36]));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase(DLG_TEXT_BASE[37], DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]) + DLG_TEXT_BASE[40]+ GetFullName(Pchar)+ LinkRandPhrase(DLG_TEXT_BASE[41]+NPCharSexPhrase(NPChar,"",DLG_TEXT_BASE[42])+DLG_TEXT_BASE[43]+NPCharSexPhrase(NPChar,DLG_TEXT_BASE[44],"?"), DLG_TEXT_BASE[45], DLG_TEXT_BASE[46]),
                                LinkRandPhrase(DLG_TEXT_BASE[47] + GetFullName(Pchar) + DLG_TEXT_BASE[48], DLG_TEXT_BASE[49] + GetFullName(Pchar) + ".", DLG_TEXT_BASE[50] + GetFullName(Pchar)));
				Link.l1.go = "Meeting";
			}
			else
			{
				link.l1 = PCharRepPhrase(DLG_TEXT_BASE[55], DLG_TEXT_BASE[56]);
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple(DLG_TEXT_BASE[59], DLG_TEXT_BASE[60]);
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = DLG_TEXT_BASE[242]+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[243];
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase(DLG_TEXT_BASE[244],DLG_TEXT_BASE[245],DLG_TEXT_BASE[246]) + DLG_TEXT_BASE[247]);
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Oh ! C'est vous, "+GetFullName(Pchar)
                        +" "+ DLG_TEXT_BASE[72] +".", GetSexPhrase(DLG_TEXT_BASE[73],DLG_TEXT_BASE[71]) +" "
                        + Pchar.name, DLG_TEXT_BASE[74] +""
                         +GetFullName(Pchar))
                                        +LinkRandPhrase(DLG_TEXT_BASE[75], DLG_TEXT_BASE[76], DLG_TEXT_BASE[77])
                                        +LinkRandPhrase(DLG_TEXT_BASE[78], DLG_TEXT_BASE[79], DLG_TEXT_BASE[80]),
                                        LinkRandPhrase(TimeGreeting() + DLG_TEXT_BASE[81], DLG_TEXT_BASE[82]+GetAddress_Form(NPChar)+" ", DLG_TEXT_BASE[83])+GetFullName(Pchar)
                                        +LinkRandPhrase(DLG_TEXT_BASE[84], DLG_TEXT_BASE[85], DLG_TEXT_BASE[86])

                                        ),
                                        
                        PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[87], DLG_TEXT_BASE[88]+GetAddress_Form(NPChar)+" ", DLG_TEXT_BASE[89])
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(DLG_TEXT_BASE[90]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[91])+DLG_TEXT_BASE[92],
                                                         DLG_TEXT_BASE[93]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[94])+DLG_TEXT_BASE[95], DLG_TEXT_BASE[96])
                                        +LinkRandPhrase(DLG_TEXT_BASE[97], DLG_TEXT_BASE[98], DLG_TEXT_BASE[99]+NPCharSexPhrase(NPChar, DLG_TEXT_BASE[100], DLG_TEXT_BASE[101])),
                                        LinkRandPhrase(TimeGreeting() + DLG_TEXT_BASE[102] + GetFullName(Pchar) + DLG_TEXT_BASE[103],
                                        DLG_TEXT_BASE[104] + GetFullName(Pchar) + DLG_TEXT_BASE[105],
                                        DLG_TEXT_BASE[106] + GetAddress_Form(NPChar) + " " + Pchar.lastname + DLG_TEXT_BASE[107]))
                                        );                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[108], DLG_TEXT_BASE[109]),
                                        RandPhraseSimple(DLG_TEXT_BASE[110], DLG_TEXT_BASE[111]));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = DLG_TEXT_BASE[248];
			link.l1 = DLG_TEXT_BASE[249];
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[250],
										DLG_TEXT_BASE[251] + GetFullName(Pchar) + ".", 
										DLG_TEXT_BASE[252] + GetFullName(Pchar) + DLG_TEXT_BASE[253]);
			link.l1 = DLG_TEXT_BASE[254];
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[112] + GetFullName(Pchar)+"?",
                                                                    DLG_TEXT_BASE[113] + PChar.name+"?",
                                                                    DLG_TEXT_BASE[114] + GetFullName(Pchar)+".")
                                                                     + DLG_TEXT_BASE[115],
                                                    LinkRandPhrase(DLG_TEXT_BASE[116] + PChar.name,
                                                                    DLG_TEXT_BASE[117]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[118])+DLG_TEXT_BASE[119] + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     DLG_TEXT_BASE[120] + PChar.name) + DLG_TEXT_BASE[121]);

            link.l1 = PCharRepPhrase(DLG_TEXT_BASE[122], DLG_TEXT_BASE[123]);
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple(DLG_TEXT_BASE[124], DLG_TEXT_BASE[125]);
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple(DLG_TEXT_BASE[126], DLG_TEXT_BASE[127]);
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = DLG_TEXT_BASE[255]+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[256];
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase(DLG_TEXT_BASE[257],DLG_TEXT_BASE[258],DLG_TEXT_BASE[259]) + DLG_TEXT_BASE[260]);
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[138], DLG_TEXT_BASE[139]),
                                        RandPhraseSimple(DLG_TEXT_BASE[140], DLG_TEXT_BASE[141]));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[142]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[143])+DLG_TEXT_BASE[144], DLG_TEXT_BASE[145], DLG_TEXT_BASE[146] + PChar.name + "?"),
                                        LinkRandPhrase(DLG_TEXT_BASE[147], DLG_TEXT_BASE[148]+PChar.name+DLG_TEXT_BASE[149], DLG_TEXT_BASE[150])),
		                PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[151]+ GetAddress_Form(NPChar) + "?", DLG_TEXT_BASE[152], DLG_TEXT_BASE[153]),
                                        LinkRandPhrase(DLG_TEXT_BASE[154]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[155])+DLG_TEXT_BASE[156] + GetAddress_Form(NPChar) + " " + PChar.lastname + DLG_TEXT_BASE[157],
                                                        DLG_TEXT_BASE[158] + GetAddress_Form(NPChar) + "?",
                                                        DLG_TEXT_BASE[159])));
			link.l1 = LinkRandPhrase (DLG_TEXT_BASE[160],
                                    DLG_TEXT_BASE[161],
                                    DLG_TEXT_BASE[162]);
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[163], DLG_TEXT_BASE[164], DLG_TEXT_BASE[165]);
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple(DLG_TEXT_BASE[318], DLG_TEXT_BASE[319]);
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple(DLG_TEXT_BASE[320], DLG_TEXT_BASE[321]);
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[172], DLG_TEXT_BASE[173]),
                                        RandPhraseSimple(DLG_TEXT_BASE[174], DLG_TEXT_BASE[175]));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = DLG_TEXT_BASE[261];
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = DLG_TEXT_BASE[262];
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = DLG_TEXT_BASE[263];
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = DLG_TEXT_BASE[264];
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = DLG_TEXT_BASE[265];
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = DLG_TEXT_BASE[266];
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = DLG_TEXT_BASE[267];
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+DLG_TEXT_BASE[268]+ NPCharSexPhrase(npchar, "","") +".";
			link.l1 = DLG_TEXT_BASE[269]+pchar.GenQuest.Device.Shipyarder.Describe+DLG_TEXT_BASE[270];
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = DLG_TEXT_BASE[271];
				link.l1 = DLG_TEXT_BASE[272];
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[273];
				link.l1 = DLG_TEXT_BASE[274];
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[308],DLG_TEXT_BASE[309],DLG_TEXT_BASE[310]);
					link.l1 = LinkRandPhrase(DLG_TEXT_BASE[311],DLG_TEXT_BASE[312],DLG_TEXT_BASE[313]);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[314],DLG_TEXT_BASE[315],DLG_TEXT_BASE[316]);
				link.l1 = DLG_TEXT_BASE[317];
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнаженному оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[213], DLG_TEXT_BASE[214]);
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[215], DLG_TEXT_BASE[216], DLG_TEXT_BASE[217]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[218], DLG_TEXT_BASE[219]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[220], DLG_TEXT_BASE[221]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}