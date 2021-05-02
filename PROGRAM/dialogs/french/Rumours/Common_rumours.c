// Слухи - диалог по типажам
#include "SD\TEXT\DIALOGS\Common_rumours.h"
#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(DLG_TEXT_RUM[0], DLG_TEXT_RUM[1]);
            posrep2 = DLG_TEXT_RUM[2];
            answ1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[3]+GetFullName(NPChar)+".",
                                 DLG_TEXT_RUM[4]);
            answ2 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[5],DLG_TEXT_RUM[6]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[7],DLG_TEXT_RUM[8]);
            answ4 = "";
        }
        else
        {
            posrep1 = DLG_TEXT_RUM[9];
            posrep2 = DLG_TEXT_RUM[10] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[11];
            answ1 = RandPhraseSimple(DLG_TEXT_RUM[12],RandSwear() + DLG_TEXT_RUM[13]);
            answ2 = RandPhraseSimple(DLG_TEXT_RUM[14],DLG_TEXT_RUM[15]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[16],DLG_TEXT_RUM[17]);
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple(DLG_TEXT_RUM[18],DLG_TEXT_RUM[19]),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[20],DLG_TEXT_RUM[21]);
		link.l2.go = "exit";
	break;

/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(DLG_TEXT_RUM[22], DLG_TEXT_RUM[23]);
            posrep2 = DLG_TEXT_RUM[24];
            answ1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[25]+GetFullName(NPChar)+".",
                                 DLG_TEXT_RUM[26]);
            answ2 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[27],DLG_TEXT_RUM[28]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[29],DLG_TEXT_RUM[30]);
            answ4 = "";
        }
        else
        {
            posrep1 = DLG_TEXT_RUM[31];
            posrep2 = DLG_TEXT_RUM[32] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[33];
            answ1 = RandPhraseSimple(DLG_TEXT_RUM[34],RandSwear() + DLG_TEXT_RUM[35]);
            answ2 = RandPhraseSimple(DLG_TEXT_RUM[36],DLG_TEXT_RUM[37]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[38],DLG_TEXT_RUM[39]);
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple(DLG_TEXT_RUM[40],DLG_TEXT_RUM[41]),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[42],DLG_TEXT_RUM[43]);
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////---слухи темных личностей---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(DLG_TEXT_RUM[44], DLG_TEXT_RUM[45]);
            posrep2 = DLG_TEXT_RUM[46];
            answ1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[47]+GetFullName(NPChar)+".",
                                 DLG_TEXT_RUM[48]);
            answ2 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[49],DLG_TEXT_RUM[50]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[51],DLG_TEXT_RUM[52]);
            answ4 = "";
        }
        else
        {
            posrep1 = DLG_TEXT_RUM[53];
            posrep2 = DLG_TEXT_RUM[54] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[55];
            answ1 = RandPhraseSimple(DLG_TEXT_RUM[56],RandSwear() + DLG_TEXT_RUM[57]);
            answ2 = RandPhraseSimple(DLG_TEXT_RUM[58],DLG_TEXT_RUM[59]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[60],DLG_TEXT_RUM[61]);
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple(DLG_TEXT_RUM[62],DLG_TEXT_RUM[63]),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[64],DLG_TEXT_RUM[65]);
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(DLG_TEXT_RUM[66], DLG_TEXT_RUM[67]);
            posrep2 = DLG_TEXT_RUM[68];
            answ1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[69]+GetFullName(NPChar)+".",
                                 DLG_TEXT_RUM[70]);
            answ2 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[71],DLG_TEXT_RUM[72]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[73],DLG_TEXT_RUM[74]);
            answ4 = "";
        }
        else
        {
            posrep1 = DLG_TEXT_RUM[75];
            posrep2 = DLG_TEXT_RUM[76] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[77];
            answ1 = RandPhraseSimple(DLG_TEXT_RUM[78],RandSwear() + DLG_TEXT_RUM[79]);
            answ2 = RandPhraseSimple(DLG_TEXT_RUM[80],DLG_TEXT_RUM[81]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[82],DLG_TEXT_RUM[83]);
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple(DLG_TEXT_RUM[84],DLG_TEXT_RUM[85]),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[86],DLG_TEXT_RUM[87]);
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(DLG_TEXT_RUM[88], DLG_TEXT_RUM[89]);
            posrep2 = DLG_TEXT_RUM[90];
            answ1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[91]+GetFullName(NPChar)+".",DLG_TEXT_RUM[92]);
            answ2 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[93],DLG_TEXT_RUM[94]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[95],DLG_TEXT_RUM[96]);
            answ4 = "";
        }
        else
        {
            posrep1 = DLG_TEXT_RUM[97];
            posrep2 = DLG_TEXT_RUM[98] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[99];
            answ1 = RandPhraseSimple(DLG_TEXT_RUM[100],RandSwear() + DLG_TEXT_RUM[101]);
            answ2 = RandPhraseSimple(DLG_TEXT_RUM[102],DLG_TEXT_RUM[103]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[104],DLG_TEXT_RUM[105]);
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple(DLG_TEXT_RUM[106],DLG_TEXT_RUM[107]),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[108],DLG_TEXT_RUM[109]);
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(DLG_TEXT_RUM[110], DLG_TEXT_RUM[111]);
            posrep2 = DLG_TEXT_RUM[112];
            answ1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[113]+GetFullName(NPChar)+".",
                                 DLG_TEXT_RUM[114]);
            answ2 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[115],DLG_TEXT_RUM[116]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[117],DLG_TEXT_RUM[118]);
            answ4 = "";
        }
        else
        {
            posrep1 = DLG_TEXT_RUM[119];
            posrep2 = DLG_TEXT_RUM[120] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[121];
            answ1 = RandPhraseSimple(DLG_TEXT_RUM[122],RandSwear() + DLG_TEXT_RUM[123]);
            answ2 = RandPhraseSimple(DLG_TEXT_RUM[124],DLG_TEXT_RUM[125]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[126],DLG_TEXT_RUM[127]);
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple(DLG_TEXT_RUM[128],DLG_TEXT_RUM[129]),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[130],DLG_TEXT_RUM[131]);
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		Dialog.Text = LinkRandPhrase(DLG_TEXT_RUM[132],DLG_TEXT_RUM[133],DLG_TEXT_RUM[134])+SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[135],
                                 DLG_TEXT_RUM[136]);
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[137],
                                 DLG_TEXT_RUM[138]);
		link.l2.go = "exit_sit";
		if (pchar.questTemp.BlueBird.City == npchar.city && pchar.questTemp.BlueBird == "returnMoney")
		{
			Dialog.Text = BlueBird_setTradeShip();
			link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[135],
                                 DLG_TEXT_RUM[136]);
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple(DLG_TEXT_RUM[137],
                                 DLG_TEXT_RUM[138]);
			link.l2.go = "exit_sit";
			//новый слух в другом городе
			pchar.questTemp.BlueBird.City = GetSharpCity();
			break;
		}
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = DLG_TEXT_RUM[139];
            link.l1 = DLG_TEXT_RUM[140];
            link.l1.go = "Jamaica_ratH_1";
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = DLG_TEXT_RUM[141];
            link.l1 = DLG_TEXT_RUM[142];
            link.l1.go = "EscapeSlave_Villemstad_H1";
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = DLG_TEXT_RUM[143];
            link.l1 = DLG_TEXT_RUM[144];
            link.l1.go = "Lucas_Tavern";
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase(DLG_TEXT_RUM[145],DLG_TEXT_RUM[146],DLG_TEXT_RUM[147]);
            link.l1 = DLG_TEXT_RUM[148]+pchar.GenQuest.FindFugitive.Name+DLG_TEXT_RUM[149];
            link.l1.go = "FindFugitiveHb";
        }
		//<-- поиск дезертира
		
		// карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = DLG_TEXT_RUM[150];
            link.l1 = DLG_TEXT_RUM[151];
            link.l1.go = "trial_spy";
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = DLG_TEXT_RUM[152] + GetAddress_Form(pchar) + DLG_TEXT_RUM[153];
			link.l1 = DLG_TEXT_RUM[154];
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
		}
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+DLG_TEXT_RUM[155],
                strum+DLG_TEXT_RUM[156],RandPhraseSimple(DLG_TEXT_RUM[157],DLG_TEXT_RUM[158]),"block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + DLG_TEXT_RUM[159],DLG_TEXT_RUM[160]), pcharrepphrase(""+ GetSexPhrase(DLG_TEXT_RUM[161],DLG_TEXT_RUM[162]) +DLG_TEXT_RUM[163],DLG_TEXT_RUM[164]),
pcharrepphrase(RandSwear() +DLG_TEXT_RUM[165],DLG_TEXT_RUM[166]),pcharrepphrase(DLG_TEXT_RUM[167],DLG_TEXT_RUM[168]),npchar, Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(DLG_TEXT_RUM[169],
DLG_TEXT_RUM[170]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),pcharrepphrase(DLG_TEXT_RUM[171],DLG_TEXT_RUM[172]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+DLG_TEXT_RUM[173])),NPCharRepPhrase(npchar,pcharrepphrase(DLG_TEXT_RUM[174],DLG_TEXT_RUM[175]),pcharrepphrase(DLG_TEXT_RUM[176],DLG_TEXT_RUM[177])),NPCharRepPhrase(npchar,pcharrepphrase(DLG_TEXT_RUM[178],DLG_TEXT_RUM[179]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),pcharrepphrase(DLG_TEXT_RUM[180],DLG_TEXT_RUM[181]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase(DLG_TEXT_RUM[182] +GetFullName(pchar)+ DLG_TEXT_RUM[183],DLG_TEXT_RUM[184]),pcharrepphrase(DLG_TEXT_RUM[185],DLG_TEXT_RUM[186] + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[187],
                                     DLG_TEXT_RUM[188]);
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple(DLG_TEXT_RUM[189],
                                    DLG_TEXT_RUM[190]);
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[191],
                                     DLG_TEXT_RUM[192]);
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple(DLG_TEXT_RUM[193],
                                     DLG_TEXT_RUM[194]);
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06

                 Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase(DLG_TEXT_RUM[195],
                DLG_TEXT_RUM[196],
                DLG_TEXT_RUM[197]),
                DLG_TEXT_RUM[198],
                "", "", "block", 1, npchar, Dialog.CurrentNode);
             
    			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[199],
                                         DLG_TEXT_RUM[200]), DLG_TEXT_RUM[201], DLG_TEXT_RUM[202], DLG_TEXT_RUM[203], npchar, Dialog.CurrentNode);
                link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
                NextDiag.CurrentNode = NextDiag.TempNode;
    			if (makeint(pchar.money) >= 1000 )
    			{
    				link.l2 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_RUM[204], DLG_TEXT_RUM[205]),
                     "", "", "" , npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}
    			else
    			{
                    link.l2 =  HeroStringReactionRepeat(DLG_TEXT_RUM[206], "", "", "", npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text =  DLG_TEXT_RUM[207];
					link.l1 = DLG_TEXT_RUM[208];
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); //ставим Мореля
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  DLG_TEXT_RUM[408];
				link.l1 = DLG_TEXT_RUM[409];
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  DLG_TEXT_RUM[410];
				link.l1 = DLG_TEXT_RUM[411];
				link.l1.go = "FMQN_r";
				break;
			}	
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  DLG_TEXT_RUM[412];
				link.l1 = DLG_TEXT_RUM[413];
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // ставим офицера-негодяя
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				break;
			}			
            string RumText = SelectRumourEx("tavern", NPChar); //fix
            //SelectRumour();
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
                link.l1 = RandPhraseSimple(DLG_TEXT_RUM[209], DLG_TEXT_RUM[210]);

			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
			  //  link.l2 = LinkRandPhrase("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
              //                       "Всего хорошего","Спасибо, мне пора. До свидания.");
			  //  link.l2.go = "Exit";
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple(DLG_TEXT_RUM[211], DLG_TEXT_RUM[212]);
    			link.l1.go = "rumours_tavern";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			Dialog.Text = DLG_TEXT_RUM[213];
            link.l1 = DLG_TEXT_RUM[214];
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = LinkRandPhrase(DLG_TEXT_RUM[215],
                                     DLG_TEXT_RUM[216],DLG_TEXT_RUM[217]);
			link.l2.go = "Exit";
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[218],
										DLG_TEXT_RUM[219]);
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple(DLG_TEXT_RUM[220],
										DLG_TEXT_RUM[221]);
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple(DLG_TEXT_RUM[222], 
					DLG_TEXT_RUM[223]);
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[224],
										DLG_TEXT_RUM[225]);
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[226],
										DLG_TEXT_RUM[227]);
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple(DLG_TEXT_RUM[228],
										DLG_TEXT_RUM[229]);
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple(DLG_TEXT_RUM[230], 
					DLG_TEXT_RUM[231]);
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[232],
										DLG_TEXT_RUM[233]);
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[234],
										DLG_TEXT_RUM[235]);
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple(DLG_TEXT_RUM[236], DLG_TEXT_RUM[237]), 
					RandPhraseSimple(DLG_TEXT_RUM[238], DLG_TEXT_RUM[239]));
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[240], DLG_TEXT_RUM[241]);
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_RUM[242], DLG_TEXT_RUM[243]), DLG_TEXT_RUM[244], DLG_TEXT_RUM[245], DLG_TEXT_RUM[246], "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_RUM[247], DLG_TEXT_RUM[248]), DLG_TEXT_RUM[249], DLG_TEXT_RUM[250], DLG_TEXT_RUM[251] , npchar, Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple(DLG_TEXT_RUM[252], DLG_TEXT_RUM[253]);

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple(DLG_TEXT_RUM[254], DLG_TEXT_RUM[255]);
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple(DLG_TEXT_RUM[256], DLG_TEXT_RUM[257]);
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple(DLG_TEXT_RUM[258], DLG_TEXT_RUM[259]);
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple(DLG_TEXT_RUM[260], DLG_TEXT_RUM[261]);

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple(DLG_TEXT_RUM[262], DLG_TEXT_RUM[263]);
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = DLG_TEXT_RUM[264];
	        	link.l1 = DLG_TEXT_RUM[265];
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = DLG_TEXT_RUM[266];
	        	link.l1 = "" + GetAddress_FormToNPC(NPChar) + DLG_TEXT_RUM[267] +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ DLG_TEXT_RUM[268];
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = DLG_TEXT_RUM[269] + FindRussianDaysString(iTime)+ DLG_TEXT_RUM[270] + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + DLG_TEXT_RUM[271];
	        	link.l1 = DLG_TEXT_RUM[272];
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")//опоздали совсем
			{
				dialog.text = DLG_TEXT_RUM[273]+DLG_TEXT_RUM[274];
	        	link.l1 = DLG_TEXT_RUM[275];
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = DLG_TEXT_RUM[276] + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + DLG_TEXT_RUM[277];
        	link.l1 = DLG_TEXT_RUM[278];
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 120);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = DLG_TEXT_RUM[279] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[280];
			link.l1 = DLG_TEXT_RUM[281] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = DLG_TEXT_RUM[282] +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ DLG_TEXT_RUM[283] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[284];
			link.l1 = "Hm...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--почтовый генератор 2 уровня

//Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
		case "Device_Common":
			dialog.text = DLG_TEXT_RUM[285];
			link.l1 = DLG_TEXT_RUM[286];
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://в городе
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://за воротами
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://в бухте
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://в доме
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //определяем локацию
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//если вдруг мимо или взят поиск шпиона
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<-- генератор Неудачливый вор
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN_r":
			Dialog.Text =  DLG_TEXT_RUM[414];
			link.l1 = DLG_TEXT_RUM[415];
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;
		
		case "RBlueBird":
			dialog.text = DLG_TEXT_RUM[304];
			link.l1 = DLG_TEXT_RUM[305];
			link.l1.go = "RBlueBird_1";
		break;
		case "RBlueBird_1":
			dialog.text = DLG_TEXT_RUM[306];
			link.l1 = DLG_TEXT_RUM[307];
			link.l1.go = "RBlueBird_2";
		break;
		case "RBlueBird_2":
			dialog.text = DLG_TEXT_RUM[308];
			link.l1 = DLG_TEXT_RUM[309];
			link.l1.go = "RBlueBird_3";
		break;
		case "RBlueBird_3":
			dialog.text = DLG_TEXT_RUM[310];
			link.l1 = DLG_TEXT_RUM[311];
			link.l1.go = "RBlueBird_4";
		break;
		case "RBlueBird_4":
			dialog.text = DLG_TEXT_RUM[312];
			link.l1 = DLG_TEXT_RUM[313];
			link.l1.go = "RBlueBird_5";
		break;
		case "RBlueBird_5":
			dialog.text = DLG_TEXT_RUM[314];
			link.l1 = DLG_TEXT_RUM[315];
			link.l1.go = "RBlueBird_close";
			link.l2 = DLG_TEXT_RUM[316];
			link.l2.go = "RBlueBird_6";
		break;
		case "RBlueBird_6":
			dialog.text = DLG_TEXT_RUM[317];
			link.l1 = DLG_TEXT_RUM[318];
			link.l1.go = "RBlueBird_7";
		break;
		case "RBlueBird_7":
			dialog.text = DLG_TEXT_RUM[319];
			link.l1 = DLG_TEXT_RUM[320];
			link.l1.go = "RBlueBird_8";
		break;
		case "RBlueBird_8":
			dialog.text = DLG_TEXT_RUM[321] + GetAddress_Form(NPChar) + "." ;
			link.l1 = DLG_TEXT_RUM[322];
			link.l1.go = "RBlueBird_9";
		break;
		case "RBlueBird_9":
			dialog.text = DLG_TEXT_RUM[323];
			link.l1 = DLG_TEXT_RUM[324];
			link.l1.go = "RBlueBird_10";
		break;
		case "RBlueBird_10":
			dialog.text = DLG_TEXT_RUM[325];
			link.l1 = DLG_TEXT_RUM[326];
			link.l1.go = "RBlueBird_11";
		break;
		case "RBlueBird_11":
			dialog.text = DLG_TEXT_RUM[327];
			link.l1 = DLG_TEXT_RUM[328];
			link.l1.go = "RBlueBird_12";
		break;
		case "RBlueBird_12":
			dialog.text = DLG_TEXT_RUM[329];
			link.l1 = DLG_TEXT_RUM[330];
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toBermudes";
			pchar.questTemp.BlueBird.traiderId = npchar.id; //запомним Id торговца
			SetQuestHeader("Xebeca_BlueBird");
			AddQuestRecord("Xebeca_BlueBird", "1");
			AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Xebeca_BlueBird", "sName", GetFullName(npchar));
		break;


		case "RBlueBird_close":
			dialog.text = DLG_TEXT_RUM[331];
			link.l1 = DLG_TEXT_RUM[332];
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "over";
		break;
		case "RBlueBirdWon":
			pchar.questTemp.Ascold = "canTakeQuest";
			dialog.text = DLG_TEXT_RUM[333];
			link.l1 = DLG_TEXT_RUM[334];
			link.l1.go = "RBlueBirdWon_1";
            if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_XebekVML)
        	{	
				dialog.text = DLG_TEXT_RUM[335];
				link.l1 = DLG_TEXT_RUM[336];
				link.l1.go = "RBlueBirdWon_10";
				break;
            }
			for(int i=1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
					{
					dialog.text = DLG_TEXT_RUM[335];
					link.l1 = DLG_TEXT_RUM[336];
					link.l1.go = "RBlueBirdWon_10";
					break;
					}
				}
			}
		break;

		case "RBlueBirdWon_1":
			dialog.text = DLG_TEXT_RUM[337];
			link.l1 = DLG_TEXT_RUM[338];
			link.l1.go = "RBlueBirdWon_2";
			AddMoneyToCharacter(pchar, 50000);
		break;
		case "RBlueBirdWon_2":
			dialog.text = DLG_TEXT_RUM[339];
			link.l1 = DLG_TEXT_RUM[340];
			link.l1.go = "RBlueBirdWon_3";
		break;
		case "RBlueBirdWon_3":
			dialog.text = DLG_TEXT_RUM[341];
			link.l1 = DLG_TEXT_RUM[342];
			link.l1.go = "RBlueBirdWon_4";
		break;
		case "RBlueBirdWon_4":
			dialog.text = DLG_TEXT_RUM[343];
			link.l1 = DLG_TEXT_RUM[344];
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBirdWon_10":
			dialog.text = DLG_TEXT_RUM[345];
			link.l1 = DLG_TEXT_RUM[346];
			link.l1.go = "RBlueBirdWon_11";
		break;
		case "RBlueBirdWon_11":
			dialog.text = DLG_TEXT_RUM[347];
			link.l1 = DLG_TEXT_RUM[348];
			link.l1.go = "RBlueBirdWon_12";
		break;
		case "RBlueBirdWon_12":
			dialog.text = DLG_TEXT_RUM[349];
			link.l1 = DLG_TEXT_RUM[350];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "9");
			pchar.questTemp.BlueBird = "returnMoney";
			pchar.questTemp.BlueBird.City = GetSharpCity();
		break;

		case "RBlueBirdDieHard":
			dialog.text = DLG_TEXT_RUM[351];
			link.l1 = DLG_TEXT_RUM[352];
			link.l1.go = "RBlueBirdDieHard_1";
		break;
		case "RBlueBirdDieHard_1":
			dialog.text = DLG_TEXT_RUM[353];
			link.l1 = DLG_TEXT_RUM[354];
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBird_retMoney_1":
			dialog.text = DLG_TEXT_RUM[355];
			link.l1 = DLG_TEXT_RUM[356];
			link.l1.go = "RBlueBird_retMoney_2";
		break;
		case "RBlueBird_retMoney_2":
			dialog.text = DLG_TEXT_RUM[357];
			link.l1 = DLG_TEXT_RUM[358];
			link.l1.go = "fight";
		break;

		case "RBlueBird_retMoney_3":
			dialog.text = DLG_TEXT_RUM[359];
			link.l1 = DLG_TEXT_RUM[360];
			link.l1.go = "RBlueBird_retMoney_4";
		break;
		case "RBlueBird_retMoney_4":
			dialog.text = DLG_TEXT_RUM[361];
			link.l1 = DLG_TEXT_RUM[362];
			link.l1.go = "RBlueBird_retMoney_5";
		break;
		case "RBlueBird_retMoney_5":
			dialog.text = DLG_TEXT_RUM[363];
			link.l1 = DLG_TEXT_RUM[364];
			link.l1.go = "RBlueBird_retMoney_6";
		break;
		case "RBlueBird_retMoney_6":
			dialog.text = DLG_TEXT_RUM[365];
			link.l1 = DLG_TEXT_RUM[366];
			link.l1.go = "RBlueBird_retMoney_7";
		break;
		case "RBlueBird_retMoney_7":
			dialog.text = DLG_TEXT_RUM[367];
			link.l1 = DLG_TEXT_RUM[368];
			link.l1.go = "RBlueBird_retMoney_8";
		break;
		case "RBlueBird_retMoney_8":
			dialog.text = DLG_TEXT_RUM[369];
			link.l1 = DLG_TEXT_RUM[370];
			link.l1.go = "RBlueBird_retMoney_9";
		break;
		case "RBlueBird_retMoney_9":
			dialog.text = DLG_TEXT_RUM[371];
			link.l1 = DLG_TEXT_RUM[372];
			link.l1.go = "RBlueBird_retMoney_10";
		break;
		case "RBlueBird_retMoney_10":
			dialog.text = DLG_TEXT_RUM[373];
			link.l1 = DLG_TEXT_RUM[374];
			link.l1.go = "RBlueBird_retMoney_11";
		break;
		case "RBlueBird_retMoney_11":
			dialog.text = DLG_TEXT_RUM[375];
			link.l1 = DLG_TEXT_RUM[376];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlueBird");
			pchar.questTemp.BlueBird = "over"; //закрываем квест
			AddMoneyToCharacter(pchar, 200000);
			AddQuestRecord("Xebeca_BlueBird", "14");
			CloseQuestHeader("Xebeca_BlueBird");
		break;

		case "AscoldTrader": //рендомный хоз¤ин магаза
            dialog.Text = DLG_TEXT_RUM[377];
            if (GetQuestPastDayParam("questTemp.Ascold") > 3)
			{
				Link.l1 = DLG_TEXT_RUM[378];
            	Link.l1.go = "AscoldTrader_6";
			}
			else
			{
				Link.l1 = DLG_TEXT_RUM[379];
            	Link.l1.go = "quests";
			}
		break;
        case "AscoldTrader_WasSeek":
            dialog.Text = DLG_TEXT_RUM[380];
            Link.l2 = DLG_TEXT_RUM[381];
            Link.l2.go = "AscoldTrader_1";
        break;		
		case "AscoldTrader_1":
        	dialog.text = DLG_TEXT_RUM[382];
    		link.l1 = DLG_TEXT_RUM[383];
    		link.l1.go = "AscoldTrader_2";
		break;
 		case "AscoldTrader_2":
        	dialog.text = DLG_TEXT_RUM[384]+
                          DLG_TEXT_RUM[385];
                link.l1 = DLG_TEXT_RUM[387];
                link.l1.go = "AscoldTrader_4";
          
		break;

 		case "AscoldTrader_4":
        	dialog.text = DLG_TEXT_RUM[390]+
                          DLG_TEXT_RUM[391]+
                          DLG_TEXT_RUM[392]+
                          DLG_TEXT_RUM[393];
    		link.l1 = DLG_TEXT_RUM[394];
    		link.l1.go = "AscoldTrader_5";
		break;
 		case "AscoldTrader_5":
        	dialog.text = DLG_TEXT_RUM[395];
    		link.l1 = DLG_TEXT_RUM[396];
    		link.l1.go = "exit";
    	    pchar.questTemp.Ascold = "HaveRecomendation";
            AddQuestRecord("Ascold", "2");
		break;
 		case "AscoldTrader_6":
        	dialog.text = DLG_TEXT_RUM[397];
    		link.l1 = DLG_TEXT_RUM[398];
    		link.l1.go = "AscoldTrader_7";
		break;
 		case "AscoldTrader_7":
        	dialog.text = DLG_TEXT_RUM[399];
    		link.l1 = DLG_TEXT_RUM[400];
    		link.l1.go = "quests";
			SaveCurrentQuestDateParam("questTemp.Ascold");
		break;
        //==> ќбщий диалог дл¤ хоз¤ев верфи, квест јззи.
		case "AzzyTryTalk":
			dialog.Text = NPCStringReactionRepeat(DLG_TEXT_RUM[401], "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
  			Link.l1 = HeroStringReactionRepeat(DLG_TEXT_RUM[402], "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l1.go = "Exit";
		break;
		case "AggryHelp":
			dialog.Text = NPCStringReactionRepeat(DLG_TEXT_RUM[403], "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
			Link.l10 = HeroStringReactionRepeat(DLG_TEXT_RUM[404] + npchar.name + ".", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l10.go = "exit";
			items[GetItemIndex("Azzy_bottle")].shown = 0; //даем возможность вскрыть лампу
		break;
		//==> ќбщий диалог дл¤ церкви, квест јззи.
        case "GiveLamp":
			dialog.text = DLG_TEXT_RUM[405]+
                          DLG_TEXT_RUM[406];
			link.l1 = DLG_TEXT_RUM[407];
			link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 100);
            TakeItemFromCharacter(pchar, "Azzy_bottle");
		break;		
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple(DLG_TEXT_RUM[287]+DLG_TEXT_RUM[288], 
				DLG_TEXT_RUM[289]+DLG_TEXT_RUM[290]);
            link.l1 = RandPhraseSimple(DLG_TEXT_RUM[291], DLG_TEXT_RUM[292]);
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_RUM[293], DLG_TEXT_RUM[294], DLG_TEXT_RUM[295]);
			link.l1 = LinkRandPhrase(DLG_TEXT_RUM[296], DLG_TEXT_RUM[297], DLG_TEXT_RUM[298]);
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идет распределение по городам
{
	string sRetRumour = "Явный баг. Сообщите о нем АТ, для Warship'а.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = DLG_TEXT_RUM[299]+DLG_TEXT_RUM[300];
	STR_MAYOR[1] = DLG_TEXT_RUM[299]+DLG_TEXT_RUM[300];
	STR_MAYOR[2] = DLG_TEXT_RUM[299]+DLG_TEXT_RUM[300];
	STR_MAYOR[3] = DLG_TEXT_RUM[299]+DLG_TEXT_RUM[300];
	STR_MAYOR[4] = DLG_TEXT_RUM[299]+DLG_TEXT_RUM[300];
	STR_MAYOR[5] = DLG_TEXT_RUM[299]+DLG_TEXT_RUM[300];
	STR_MAYOR[6] = DLG_TEXT_RUM[299]+DLG_TEXT_RUM[300];
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = DLG_TEXT_RUM[301];
	STR_TAVERNKEEPER[1] = DLG_TEXT_RUM[301];
	STR_TAVERNKEEPER[2] = DLG_TEXT_RUM[301];
	STR_TAVERNKEEPER[3] = DLG_TEXT_RUM[301];
	STR_TAVERNKEEPER[4] = DLG_TEXT_RUM[301];
	STR_TAVERNKEEPER[5] = DLG_TEXT_RUM[301];
	STR_TAVERNKEEPER[6] = DLG_TEXT_RUM[301];
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = DLG_TEXT_RUM[302];
	STR_SHIPYARDER[1] = DLG_TEXT_RUM[302];
	STR_SHIPYARDER[2] = DLG_TEXT_RUM[302];
	STR_SHIPYARDER[3] = DLG_TEXT_RUM[302];
	STR_SHIPYARDER[4] = DLG_TEXT_RUM[302];
	STR_SHIPYARDER[5] = DLG_TEXT_RUM[302];
	STR_SHIPYARDER[6] = DLG_TEXT_RUM[302];
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = DLG_TEXT_RUM[303];
	STR_TRADER[1] = DLG_TEXT_RUM[303];
	STR_TRADER[2] = DLG_TEXT_RUM[303];
	STR_TRADER[3] = DLG_TEXT_RUM[303];
	STR_TRADER[4] = DLG_TEXT_RUM[303];
	STR_TRADER[5] = DLG_TEXT_RUM[303];
	STR_TRADER[6] = DLG_TEXT_RUM[303];
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест по доставке малявы или шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[dRand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}