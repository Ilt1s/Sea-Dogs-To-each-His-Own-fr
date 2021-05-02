#include "SD\TEXT\DIALOGS\Quest_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			link.l1 = DLG_TEXT_PRS[1];
			link.l1.go = "Exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = DLG_TEXT_PRS[28];
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = DLG_TEXT_PRS[29];
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			dialog.text = DLG_TEXT_PRS[30];
			link.l1 = DLG_TEXT_PRS[31];
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = DLG_TEXT_PRS[32];
			link.l1 = DLG_TEXT_PRS[33];
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = DLG_TEXT_PRS[34];
			link.l1 = DLG_TEXT_PRS[35];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
		break;
		
		case "Sharlie_3":
			Log_Info(DLG_TEXT_PRS[36]);
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			dialog.text = DLG_TEXT_PRS[37];
			link.l1 = DLG_TEXT_PRS[38];
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = DLG_TEXT_PRS[39];
			link.l1 = DLG_TEXT_PRS[40];
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = DLG_TEXT_PRS[41];
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			// замораживаем ГГ
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto17"); // 170712
			//создаем штурмана
			ref sld = GetCharacter(NPC_GenerateCharacter("Folke", "DeLuck", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Folke";
			sld.lastname = "Deluc";
			sld.greeting = "officer_hire";
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Folke";
			LAi_SetImmortal(sld, true);
			sld.CompanionDisable = true;
			sld.rank = 5;
			LAi_SetHP(sld, 90, 90);
			sld.money = 0;
			SetSelfSkill(sld, 25, 28, 21, 24, 22);
			SetShipSkill(sld, 10, 5, 24, 22, 25, 15, 5, 15, 18);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
			pchar.questTemp.Sharlie = "takeskiper";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
