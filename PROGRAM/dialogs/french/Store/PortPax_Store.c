#include "SD\TEXT\DIALOGS\Quest_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Azzy.GiveRum"))
            {
        		Link.l1 = DLG_TEXT_STR[172];
        	    Link.l1.go = "Step_Az6";
                if (pchar.questTemp.Azzy.GiveRum == "OK")
                {
            		Link.l1 = DLG_TEXT_STR[173];
            	    Link.l1.go = "Step_Az8";
                }
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
    			Link.l2 = DLG_TEXT_STR[174];
    			Link.l2.go = "Step_Az10";
            }
		break;
		//==============================  вест јззи ===============================
 		case "Step_Az6":
        	dialog.text = DLG_TEXT_STR[175];
    		link.l1 = DLG_TEXT_STR[176];
    		link.l1.go = "Step_Az7";
		break;

 		case "Step_Az7":
        	dialog.text = DLG_TEXT_STR[177];
    		link.l1 = DLG_TEXT_STR[178];
    		link.l1.go = "Step_Az8";
    		pchar.questTemp.Azzy.GiveRum = "OK";
		break;

 		case "Step_Az8":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[179],
                       DLG_TEXT_STR[180],
                       DLG_TEXT_STR[181],
                       DLG_TEXT_STR[182], "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[183], DLG_TEXT_STR[184], DLG_TEXT_STR[185], DLG_TEXT_STR[186], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az9", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az9":
        	dialog.text = DLG_TEXT_STR[187];
    		link.l1 = DLG_TEXT_STR[188];
    		link.l1.go = "exit";
            AddCharacterGoods(Pchar, GOOD_RUM, 300);
		break;

 		case "Step_Az10":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[189],
                                    DLG_TEXT_STR[190],
                                    DLG_TEXT_STR[191],
                                    DLG_TEXT_STR[192], "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[193], DLG_TEXT_STR[194], DLG_TEXT_STR[195], DLG_TEXT_STR[196], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az11", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az11":
        	dialog.text = DLG_TEXT_STR[197];
    		link.l1 = DLG_TEXT_STR[198];
    		link.l1.go = "Step_Az12";
		break;

 		case "Step_Az12":
        	dialog.text = DLG_TEXT_STR[199]+
                          DLG_TEXT_STR[200]+
                          DLG_TEXT_STR[201];
    		link.l1 = DLG_TEXT_STR[202];
    		link.l1.go = "exit";		
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}