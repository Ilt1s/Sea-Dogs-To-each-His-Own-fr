#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[83], DLG_TEXT_STR[84] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_STR[85] + GetAddress_Form(NPChar) + "...", DLG_TEXT_STR[86],
                          DLG_TEXT_STR[87], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[88], DLG_TEXT_STR[89]), DLG_TEXT_STR[90],
                      DLG_TEXT_STR[91], DLG_TEXT_STR[92], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Ecoutez, "+npchar.name+ DLG_TEXT_STR[264];
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = DLG_TEXT_STR[265];
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = DLG_TEXT_STR[266];
			link.l1 = DLG_TEXT_STR[267];
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = DLG_TEXT_STR[268];
			link.l2 = DLG_TEXT_STR[269];
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = DLG_TEXT_STR[270];
			link.l1 = DLG_TEXT_STR[271];
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = DLG_TEXT_STR[272] + DLG_TEXT_STR[273];
			link.l1 = DLG_TEXT_STR[274];
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = DLG_TEXT_STR[275] + DLG_TEXT_STR[276];
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = DLG_TEXT_STR[277];
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = DLG_TEXT_STR[278];
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = DLG_TEXT_STR[279];
			link.l1 = DLG_TEXT_STR[280];
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase(DLG_TEXT_STR[281],DLG_TEXT_STR[282],DLG_TEXT_STR[283]);
			link.l1 = DLG_TEXT_STR[284];
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}