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
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = "Vous avez mes marchandises dans l'entrepôt. Café, cacao et bakut. Je veux le prendre.";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "Vous avez mes marchandises de Sint Maarten dans l'entrepôt. Le baron Noel Forge l'a laissé pour moi.";
                link.l2.go = "patria_goods_3";
			}			
		break;
			
		case "patria_goods":
			dialog.text = "Oui, c'est vrai, capitaine, les marchandises sont avec moi, vous attendent. Prenez-le?";
			link.l1 = "Oui";
			link.l1.go = "patria_goods_1";
			link.l2 = "Attends, je vais d'abord vérifier s'il y a de la place pour lui dans les cales.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "Super. Je vais ordonner aux porteurs de l'emmener à la jetée.";
			link.l1 = "Avoir accepté!";
			link.l1.go = "patria_goods_2";
		break;
		
		case "patria_goods_2":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.Goods");
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE) + 500);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE) + 500);
			SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(pchar, GOOD_SANDAL) + 50);
		break;
		
		case "patria_goods_3":
			dialog.text = "Oui, c'est vrai, je le garde à l'ordre du baron. Prenez-le?";
			link.l1 = "Oui.";
			link.l1.go = "patria_goods_4";
			link.l2 = "Attends, je vais d'abord vérifier s'il y a de la place pour lui dans les cales.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "Super. Je vais ordonner aux porteurs de l'emmener à la jetée.";
			link.l1 = "Avoir accepté!";
			link.l1.go = "patria_goods_5";
		break;
		
		case "patria_goods_5":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.GoodsSM"); // 17-add
			SetCharacterGoods(pchar, GOOD_TOBACCO, GetCargoGoods(pchar, GOOD_TOBACCO) + 500);
			SetCharacterGoods(pchar, GOOD_EBONY, GetCargoGoods(pchar, GOOD_EBONY) + 200);
			SetCharacterGoods(pchar, GOOD_MAHOGANY, GetCargoGoods(pchar, GOOD_MAHOGANY) + 250);
			SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + 200);
			SetCharacterGoods(pchar, GOOD_SILVER, GetCargoGoods(pchar, GOOD_SILVER) + 400);
			SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(pchar, GOOD_SHIPSILK) + 200);
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);
}