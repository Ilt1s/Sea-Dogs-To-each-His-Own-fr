#include "SD\TEXT\DIALOGS\Enc_FriendGirl_dialog.h"
void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0],
				DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3],
				DLG_TEXT_BASE[4],
				DLG_TEXT_BASE[5]);
			Link.l1.go = "Step_1";			
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[6],
				DLG_TEXT_BASE[7],
				DLG_TEXT_BASE[8]);
			Link.l1 = DLG_TEXT_BASE[9];
			Link.l1.go = "Step_2";			
		break;
		case "Step_2":
			dialog.text = DLG_TEXT_BASE[10];
			Link.l1 = DLG_TEXT_BASE[11];
			Link.l1.go = "Step_3";			
		break;		
		case "Step_3":
			dialog.text = DLG_TEXT_BASE[12];
			Link.l1 = DLG_TEXT_BASE[13];
			Link.l1.go = "Step_agree";
			Link.l2 = DLG_TEXT_BASE[14];
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //���������
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //�������� �� �������� 1 ����
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //�������� �� ������� 1 ����
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirlF.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirlF.locationId; //���� ��� �������� �������
				string model[10];
				model[0] = "citiz_41";
				model[1] = "citiz_42";
				model[2] = "citiz_43";
				model[3] = "citiz_44";
				model[4] = "citiz_45";
				model[5] = "citiz_46";
				model[6] = "citiz_47";
				model[7] = "citiz_48";
				model[8] = "citiz_49";
				model[9] = "citiz_50";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						sld.money = iRank*200+1000+rand(500);
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //� ������ ����� 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, PIRATE, 1, false, "citizen"));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground1";//+ iTemp; //����� ������ ��������� �����: 0-��������, 1-���� ������
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //�����. �������
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "monsters", "monster"+(rand(9)+1));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DialogExit();
		break;			
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = DLG_TEXT_BASE[15];
			Link.l1 = DLG_TEXT_BASE[16];
			Link.l1.go = "exit";
		break;

		case "Underground0": //����� ������� �����������
            dialog.text = DLG_TEXT_BASE[17];
			Link.l1 = DLG_TEXT_BASE[18];
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = DLG_TEXT_BASE[19];
			Link.l1 = DLG_TEXT_BASE[20];
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = DLG_TEXT_BASE[21] + GetAddress_Form(NPChar) + ".";
			Link.l1 = DLG_TEXT_BASE[22];
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //������ �������
            dialog.text = DLG_TEXT_BASE[23];
			Link.l1 = DLG_TEXT_BASE[24];
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = DLG_TEXT_BASE[25];
			Link.l1 = DLG_TEXT_BASE[26];
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = DLG_TEXT_BASE[27];
			Link.l1 = DLG_TEXT_BASE[28];
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = DLG_TEXT_BASE[29];
			Link.l1 = DLG_TEXT_BASE[30];
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = DLG_TEXT_BASE[31];
			Link.l1 = DLG_TEXT_BASE[32];
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = DLG_TEXT_BASE[33];
			Link.l1 = DLG_TEXT_BASE[34];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = DLG_TEXT_BASE[35];
			Link.l1 = DLG_TEXT_BASE[36];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}