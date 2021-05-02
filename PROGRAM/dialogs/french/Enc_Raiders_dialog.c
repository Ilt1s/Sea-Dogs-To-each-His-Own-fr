#include "SD\TEXT\DIALOGS\Enc_Raiders_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[0] + GetFullName(npchar) + DLG_TEXT_BASE[1] + FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[2], 
				DLG_TEXT_BASE[3] + GetFullName(pchar) + DLG_TEXT_BASE[4] + FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[5] + GetFullName(npchar) + DLG_TEXT_BASE[6], 
				DLG_TEXT_BASE[7] + GetMainCharacterNameGen() + DLG_TEXT_BASE[8] + FindRussianMoneyString(iMoney) + " !"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[9] + GetFullName(npchar) + DLG_TEXT_BASE[10], 
				DLG_TEXT_BASE[11] + GetFullName(pchar) + DLG_TEXT_BASE[12] + GetFullName(npchar) + DLG_TEXT_BASE[13], 
				DLG_TEXT_BASE[14] + GetFullName(npchar) + DLG_TEXT_BASE[15] + GetMainCharacterNameGen() + DLG_TEXT_BASE[16]), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[17],
				DLG_TEXT_BASE[18],
				DLG_TEXT_BASE[19]),
				LinkRandPhrase(DLG_TEXT_BASE[84]+ GetSexPhrase(DLG_TEXT_BASE[85],DLG_TEXT_BASE[86]) +DLG_TEXT_BASE[87],
				DLG_TEXT_BASE[88],
				DLG_TEXT_BASE[89]+ GetSexPhrase(DLG_TEXT_BASE[90],DLG_TEXT_BASE[91]) +DLG_TEXT_BASE[92]),
				DLG_TEXT_BASE[93]+ GetSexPhrase(DLG_TEXT_BASE[94],DLG_TEXT_BASE[95]) +DLG_TEXT_BASE[96]);				
			Link.l1 = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[20],DLG_TEXT_BASE[21], DLG_TEXT_BASE[97]), DLG_TEXT_BASE[22], DLG_TEXT_BASE[98]);
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[23], 
				DLG_TEXT_BASE[99],
				DLG_TEXT_BASE[100]),
				LinkRandPhrase(DLG_TEXT_BASE[25],
				DLG_TEXT_BASE[101],
				DLG_TEXT_BASE[24]),
				LinkRandPhrase(RandPhraseSimple(DLG_TEXT_BASE[102],
				DLG_TEXT_BASE[103]+ GetSexPhrase(DLG_TEXT_BASE[104],DLG_TEXT_BASE[105]) +"."),
				DLG_TEXT_BASE[106],
				DLG_TEXT_BASE[107]));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase(DLG_TEXT_BASE[108], 
				RandPhraseSimple(DLG_TEXT_BASE[109], 
				DLG_TEXT_BASE[110]),
				RandPhraseSimple(DLG_TEXT_BASE[111],
				DLG_TEXT_BASE[112]));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[26],
				DLG_TEXT_BASE[27],
				DLG_TEXT_BASE[113]),
				RandPhraseSimple(DLG_TEXT_BASE[114],
				DLG_TEXT_BASE[115]),
				DLG_TEXT_BASE[28]);
			Link.l1 = DLG_TEXT_BASE[29] + makeint(makeint(Pchar.money)/20)*10 + DLG_TEXT_BASE[30];
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[31],
				DLG_TEXT_BASE[116],
				DLG_TEXT_BASE[117]+ GetSexPhrase(DLG_TEXT_BASE[118],DLG_TEXT_BASE[119]) +" !"),
				LinkRandPhrase(DLG_TEXT_BASE[120],
				DLG_TEXT_BASE[121],
				DLG_TEXT_BASE[122]),
				RandPhraseSimple(DLG_TEXT_BASE[123],
				DLG_TEXT_BASE[124]));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[125], 
					DLG_TEXT_BASE[126]);
				Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[127], DLG_TEXT_BASE[128]);
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk1 = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41;
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[129], 
						DLG_TEXT_BASE[130]);
					Link.l1 = DLG_TEXT_BASE[131];
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[132], 
						DLG_TEXT_BASE[133]);
					Link.l1 = DLG_TEXT_BASE[134] + makeint(makeint(Pchar.money)/20)*10 + " pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_BASE[135], 
						DLG_TEXT_BASE[136],
						DLG_TEXT_BASE[137]),
						DLG_TEXT_BASE[138]);
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
			bool z_ok = (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30);
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple(DLG_TEXT_BASE[32],
					DLG_TEXT_BASE[33]),
					DLG_TEXT_BASE[34],
					DLG_TEXT_BASE[139]+ GetSexPhrase(DLG_TEXT_BASE[140],DLG_TEXT_BASE[141]) +DLG_TEXT_BASE[142]+ GetSexPhrase(DLG_TEXT_BASE[143],"") +DLG_TEXT_BASE[144]);
				Link.l1 = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[35],
					DLG_TEXT_BASE[36],
					DLG_TEXT_BASE[37]),
					RandPhraseSimple(DLG_TEXT_BASE[145],
					DLG_TEXT_BASE[146]),	
					RandPhraseSimple(DLG_TEXT_BASE[147],
					DLG_TEXT_BASE[148]));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase(DLG_TEXT_BASE[38],
					DLG_TEXT_BASE[39],
					DLG_TEXT_BASE[40]);
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[41],
								DLG_TEXT_BASE[42],
								DLG_TEXT_BASE[43]);
				Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[149],DLG_TEXT_BASE[44]);
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple(DLG_TEXT_BASE[45],
					DLG_TEXT_BASE[46]),
					DLG_TEXT_BASE[150],
					DLG_TEXT_BASE[47]);
				Link.l1 = DLG_TEXT_BASE[48];
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[49];
				Link.l1 = DLG_TEXT_BASE[50];
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[51],
				DLG_TEXT_BASE[52],
				DLG_TEXT_BASE[53]);
			Link.l1 = DLG_TEXT_BASE[54];
			Link.l1.go = "Exit";
			Link.l2 = DLG_TEXT_BASE[55];
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[56],
				DLG_TEXT_BASE[57],
				DLG_TEXT_BASE[58]);
			Link.l1 = DLG_TEXT_BASE[59];
			Link.l1.go = "Exit";
			Link.l2 = DLG_TEXT_BASE[60];
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[61],
				DLG_TEXT_BASE[62],
				DLG_TEXT_BASE[63]);
			Link.l1 = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[64],
				DLG_TEXT_BASE[151],
				DLG_TEXT_BASE[64]),
				DLG_TEXT_BASE[152],
				DLG_TEXT_BASE[83]);
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}