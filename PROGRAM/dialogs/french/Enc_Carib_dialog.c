#include "SD\TEXT\DIALOGS\Enc_Carib_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "явный баг. —ообщите Jason'у, как и при каких обсто€тельствах его получили.";
			link.l1 = "ќб€зательно сообщу!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
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
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(0.25);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[2],""+npchar.name+DLG_TEXT_BASE[3],DLG_TEXT_BASE[4]+npchar.name+DLG_TEXT_BASE[5]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[6],DLG_TEXT_BASE[7]);
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[8],DLG_TEXT_BASE[9]);
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[10],DLG_TEXT_BASE[11],DLG_TEXT_BASE[12]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[13],DLG_TEXT_BASE[14]);
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[15],DLG_TEXT_BASE[16]);
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > drand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple(DLG_TEXT_BASE[17],DLG_TEXT_BASE[18]);
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > drand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[19],DLG_TEXT_BASE[20]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[21],DLG_TEXT_BASE[22]);
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[23],DLG_TEXT_BASE[24]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[25],DLG_TEXT_BASE[26]);
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[27],DLG_TEXT_BASE[28]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[29],DLG_TEXT_BASE[30]);
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = DLG_TEXT_BASE[31];
				link.l1 = DLG_TEXT_BASE[32];
				link.l1.go = "war_indian_trade";
				link.l2 = DLG_TEXT_BASE[33];
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[34];
				link.l1 = DLG_TEXT_BASE[35];
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[36],DLG_TEXT_BASE[37]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[38],DLG_TEXT_BASE[39]);
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = DLG_TEXT_BASE[40];
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (drand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = drand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[41];
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(9)+14);
				iTotalTemp = drand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[42];
			}
			dialog.text = DLG_TEXT_BASE[43]+sText+".";
			link.l1 = DLG_TEXT_BASE[44];
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_TEXT_BASE[45];
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (drand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = drand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[46];
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(3)+1);
				iTotalTemp = drand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[47];
			}
			dialog.text = DLG_TEXT_BASE[48]+sText+".";
			link.l1 = DLG_TEXT_BASE[49];
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_TEXT_BASE[50];
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (drand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = drand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[51];
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(2)+2);
				iTotalTemp = drand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[52];
			}
			dialog.text = DLG_TEXT_BASE[53]+sText+".";
			link.l1 = DLG_TEXT_BASE[54];
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_TEXT_BASE[55];
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (drand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = drand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[56];
			}
			else
			{
				npchar.quest.item = "obereg_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = DLG_TEXT_BASE[57];
			}
			dialog.text = DLG_TEXT_BASE[58]+sText+".";
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_TEXT_BASE[60]
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (drand(7) < 7)
			{
				if (drand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+drand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = drand(4)+10;
				}
				qty = drand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = drand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[61];
			}
			else
			{
				npchar.quest.item = "indian_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = DLG_TEXT_BASE[62];
			}
			dialog.text = DLG_TEXT_BASE[63]+sText+".";
			link.l1 = DLG_TEXT_BASE[64];
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_TEXT_BASE[65];
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (drand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = drand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[66];
			}
			else
			{
				npchar.quest.item = "amulet_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = DLG_TEXT_BASE[67];
			}
			dialog.text = DLG_TEXT_BASE[68]+sText+".";
			link.l1 = DLG_TEXT_BASE[69];
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_TEXT_BASE[70];
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(0.3);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info(DLG_TEXT_BASE[71]+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info(DLG_TEXT_BASE[72]+XI_ConvertString(npchar.quest.item)+DLG_TEXT_BASE[73]+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+drand(2));
			{
				dialog.text = DLG_TEXT_BASE[74];
				link.l1 = DLG_TEXT_BASE[75];
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[76];
				if (CheckCaribGuns())
				{
					link.l1 = DLG_TEXT_BASE[77];
					link.l1.go = "war_indian_trade";
				}
				link.l2 = DLG_TEXT_BASE[78];
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = DLG_TEXT_BASE[79];
			link.l1 = DLG_TEXT_BASE[80];
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[81];
				link.l1 = DLG_TEXT_BASE[82];
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[83],DLG_TEXT_BASE[84],DLG_TEXT_BASE[85]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[86],DLG_TEXT_BASE[87]);
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[88],DLG_TEXT_BASE[89]);
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[90],DLG_TEXT_BASE[91]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[92],DLG_TEXT_BASE[93]);
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[94],DLG_TEXT_BASE[95]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[96],DLG_TEXT_BASE[97]);
			link.l1.go = "exit_fight";
		break;
	}
}