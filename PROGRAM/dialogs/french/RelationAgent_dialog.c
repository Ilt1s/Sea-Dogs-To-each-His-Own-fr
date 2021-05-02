#define DIPLOMAT_SUM 80000
#include "SD\TEXT\DIALOGS\RelationAgent_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;
	
	if (!CheckAttribute(npchar, "PatentPrice"))
    {
        npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;
	
    attrLoc   = Dialog.CurrentNode;
    
    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "patent_2";
 	}
 	
 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}
 	
 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
		// �������� �� ��� �������
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else
		{
 	    	Dialog.CurrentNode = "RelationAny_Done";
 	    	npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation));
 	    }
 	}
 	
 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "CityInfo";
 	}
 	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = DLG_TEXT_BASE[0];
			link.l1 = DLG_TEXT_BASE[1];
			link.l1.go = "relation";
			link.l2 = DLG_TEXT_BASE[2];
			link.l2.go = "exit";
			// ���������  "��������� ���������"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = DLG_TEXT_BASE[113];
				link.l4.go = "D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[5];
				link.l1 = DLG_TEXT_BASE[6];
				link.l1.go = "relation";
				link.l2 = DLG_TEXT_BASE[7];
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** v�������� - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = DLG_TEXT_BASE[114];
			s1 = DLG_TEXT_BASE[115];
			s1 = s1 + DLG_TEXT_BASE[116];
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = DLG_TEXT_BASE[117]+ GetSexPhrase(DLG_TEXT_BASE[118],DLG_TEXT_BASE[119]) +" ! ";
			s1 = s1 + DLG_TEXT_BASE[120] + sti(pchar.questTemp.different.GiveShipLetters.price5) + DLG_TEXT_BASE[121];
			dialog.text = s1;
			link.l1 = DLG_TEXT_BASE[122];
			link.l1.go = "D_ShipLetters_3";
			link.l2 = DLG_TEXT_BASE[123];
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "relation":
			dialog.text = DLG_TEXT_BASE[8];
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = DLG_TEXT_BASE[9];
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = DLG_TEXT_BASE[10];
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = DLG_TEXT_BASE[11];
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = DLG_TEXT_BASE[12];
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = DLG_TEXT_BASE[13];
				Link.l5.go = "Contraband";
            }
            Link.l8 = DLG_TEXT_BASE[14];
			Link.l8.go = "patent_0";
			
			Link.l9 = DLG_TEXT_BASE[15];
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = DLG_TEXT_BASE[16];
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = DLG_TEXT_BASE[17];
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = DLG_TEXT_BASE[18];
		    link.l1 = DLG_TEXT_BASE[19];
			link.l1.go = "SetNationLicence_0";
		    link.l2 = DLG_TEXT_BASE[20];
			link.l2.go = "SetNationLicence_1";
		    link.l3 = DLG_TEXT_BASE[21];
			link.l3.go = "SetNationLicence_2";
		    link.l4 = DLG_TEXT_BASE[22];
			link.l4.go = "SetNationLicence_3";
			link.l9 = DLG_TEXT_BASE[23];
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = DLG_TEXT_BASE[24];
		    link.l1 = DLG_TEXT_BASE[25];
			link.l1.go = "NationLicenceType_30";
		    link.l2 = DLG_TEXT_BASE[26];
			link.l2.go = "NationLicenceType_60";
		    link.l3 = DLG_TEXT_BASE[27];
			link.l3.go = "NationLicenceType_90";
			link.l9 = DLG_TEXT_BASE[28];
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = DLG_TEXT_BASE[29] + XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen") + DLG_TEXT_BASE[30] + sti(npchar.LicenceType) + DLG_TEXT_BASE[31] + FindRussianMoneyString(iSumm) + ".";
		    link.l1 = DLG_TEXT_BASE[32];
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = DLG_TEXT_BASE[33];
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = DLG_TEXT_BASE[34];
			link.l9 = DLG_TEXT_BASE[35];
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = DLG_TEXT_BASE[36];
			link.l1 = DLG_TEXT_BASE[37];
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = DLG_TEXT_BASE[38] + 
                          DLG_TEXT_BASE[39] + //NationNameGenitive(sti(NPChar.nation)) +
                          DLG_TEXT_BASE[40];
			link.l1 = DLG_TEXT_BASE[41]+GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[42];
			link.l1.go = "patent_1";
			link.l2 = DLG_TEXT_BASE[43]+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = DLG_TEXT_BASE[44];
			link.l1 = DLG_TEXT_BASE[45];
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = DLG_TEXT_BASE[46]+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = DLG_TEXT_BASE[47];
            link.l1 = DLG_TEXT_BASE[48]+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = DLG_TEXT_BASE[49];
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = DLG_TEXT_BASE[50];
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = DLG_TEXT_BASE[51];
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = DLG_TEXT_BASE[52];
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = DLG_TEXT_BASE[53];
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = DLG_TEXT_BASE[54];
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = DLG_TEXT_BASE[55];
                    link.l1 = DLG_TEXT_BASE[56];
                    break;
                case HOLLAND :
                    dialog.text = DLG_TEXT_BASE[57]+pchar.PatentPrice+DLG_TEXT_BASE[58];
                    link.l1 = DLG_TEXT_BASE[59];
                    break;
                case FRANCE :
                    dialog.text = DLG_TEXT_BASE[60]+pchar.PatentPrice+DLG_TEXT_BASE[61];
                    link.l1 = DLG_TEXT_BASE[62];
                    break;
                case SPAIN :
                    dialog.text = DLG_TEXT_BASE[63]+pchar.PatentPrice+DLG_TEXT_BASE[64];
                    link.l1 = DLG_TEXT_BASE[65];
                    break;
                case ENGLAND :
                    dialog.text = DLG_TEXT_BASE[66]+pchar.PatentPrice+DLG_TEXT_BASE[67];
                    link.l1 = DLG_TEXT_BASE[68];
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = DLG_TEXT_BASE[69];
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71]+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation.nobility)*DIPLOMAT_SUM);
			dialog.Text = DLG_TEXT_BASE[72] + Pchar.questTemp.Relations.sum + DLG_TEXT_BASE[73];
			Link.l1 = DLG_TEXT_BASE[74];
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = DLG_TEXT_BASE[75];
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = DLG_TEXT_BASE[76];
			Link.l99 = DLG_TEXT_BASE[77];
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = DLG_TEXT_BASE[78]+ XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Abl") +DLG_TEXT_BASE[79] + FindRussianMoneyString(iSumm) + ".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = DLG_TEXT_BASE[80];
				link.l1.go = "relation3";
			}
			link.l2 = DLG_TEXT_BASE[81];
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[83];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = DLG_TEXT_BASE[84];
			Link.l99 = DLG_TEXT_BASE[85];
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = DLG_TEXT_BASE[86];
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = DLG_TEXT_BASE[87];
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = DLG_TEXT_BASE[88] + GetCityName(colonies[i].id) + DLG_TEXT_BASE[89] + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen") + DLG_TEXT_BASE[90] + FindRussianMoneyString(iSumm) + ".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = DLG_TEXT_BASE[91];
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = DLG_TEXT_BASE[92];
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = DLG_TEXT_BASE[93] + GetCityName(colonies[i].id) + DLG_TEXT_BASE[94];
			Link.l2 = DLG_TEXT_BASE[95];
			Link.l2.go = "exit";
			Link.l3 = DLG_TEXT_BASE[96];
			Link.l3.go = "relation";
		break;
	}
}

