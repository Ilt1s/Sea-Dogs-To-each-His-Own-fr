#include "SD\TEXT\DIALOGS\Quest_usurer.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[0], DLG_TEXT_USR[1]), DLG_TEXT_USR[2], DLG_TEXT_USR[3],
                          DLG_TEXT_USR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[5], DLG_TEXT_USR[6]), DLG_TEXT_USR[7],
                      DLG_TEXT_USR[8], DLG_TEXT_USR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "usurer" && !CheckAttribute(npchar, "quest.TrialTalk1"))
            {
                link.l1 = "";
                link.l1.go = "trial";
            }
			if (CheckAttribute(pchar, "questTemp.Azzy.GiveMoney"))
            {
                link.l5 = DLG_TEXT_USR[110];
                link.l5.go = "Step_Az_1";
            }
			if (!CheckAttribute(pchar, "questTemp.Azzy.GiveMoney") && pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
                link.l5 = DLG_TEXT_USR[111];
                link.l5.go = "Step_Az_4";
            }			
		break;
		
		case "Step_Az_1":
			dialog.text = DLG_TEXT_USR[112] + GetAddress_Form(NPChar) + DLG_TEXT_USR[113];
			Link.l1 = DLG_TEXT_USR[114];
			Link.l1.go = "Step_Az_2";
		break;
		case "Step_Az_2":
			dialog.text = DLG_TEXT_USR[115] + GetAddress_Form(NPChar) + DLG_TEXT_USR[116];
			Link.l1 = DLG_TEXT_USR[117];
			Link.l1.go = "Step_Az_3";
            DeleteAttribute(pchar, "questTemp.Azzy.GiveMoney");
            AddMoneyToCharacter(pchar, 3000000);
		break;
		case "Step_Az_3":
			dialog.text = DLG_TEXT_USR[118];
			Link.l1 = DLG_TEXT_USR[119];
			Link.l1.go = "exit";
		break;
		case "Step_Az_4":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_USR[120], DLG_TEXT_USR[121], DLG_TEXT_USR[122], DLG_TEXT_USR[123], "block", 0, npchar, Dialog.CurrentNode);
			Link.l1 = HeroStringReactionRepeat(DLG_TEXT_USR[124], DLG_TEXT_USR[125], DLG_TEXT_USR[126], DLG_TEXT_USR[127], npchar, Dialog.CurrentNode);
			Link.l1.go = DialogGoNodeRepeat("Step_Az_5", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_Az_5":
			dialog.text = DLG_TEXT_USR[128]+
                     DLG_TEXT_USR[129]+
                     DLG_TEXT_USR[130]+
                     DLG_TEXT_USR[131];
			Link.l1 = DLG_TEXT_USR[132];
			Link.l1.go = "exit";
		break;
		
		case "trial":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

