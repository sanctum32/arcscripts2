/*
 * ArcScripts2 Scripts for Arcemu MMORPG Server
 * Copyright (C) 2011-2012 ArcScripts2 team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Setup.h"

class HaaleshiAltar : public GameObjectAIScript
{
	public:
		HaaleshiAltar(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript *Create(GameObject * GO) { return new HaaleshiAltar(GO); }

		void OnActivate(Player * plr)
		{
			if(plr->HasQuest(9418))
				sEAS.SpawnCreature(plr, 17085, -1323.14f, 4042.12f, 117.0f, plr->GetOrientation()+float(M_PI), 360000);
		}
};

/*--------------------------------------------------------------------------------------------------------*/
// Zeth'Gor Must Burn!

class ZethGorMustBurnAlliance : public GameObjectAIScript
{
	public:
		ZethGorMustBurnAlliance(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new ZethGorMustBurnAlliance(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10895);
			if(pQuest != NULL)
			{
				// M4ksiu - WTF IS THIS FOR? :|
				float SSX = pPlayer->GetPositionX();
				float SSY = pPlayer->GetPositionY();
				float SSZ = pPlayer->GetPositionZ();

				GameObject* pBeacon = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(SSX, SSY, SSZ, 184661);
				if(pBeacon != NULL && pBeacon->GetUInt32Value(GAMEOBJECT_FLAGS) > 0)
				{
					pBeacon->SetUInt32Value(GAMEOBJECT_FLAGS, (pBeacon->GetUInt32Value(GAMEOBJECT_FLAGS) - 1));
				}

				// Northern Zeth'Gor Tower
				if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
				{
					GameObject* pNorthern = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-820.0f, 2029.0f, 55.0f, 300150);
					if(pNorthern != NULL && pPlayer->CalcDistance(pPlayer, pNorthern) < 40)      // if reduced the server will crash when out of range
					{
						pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
						pQuest->SendUpdateAddKill(0);
						pQuest->UpdatePlayerFields();

						GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -819.77f, 2029.09f, 55.6082f, 0, 4, 0, 0, 0, 0);
						if(pGameobject != NULL)
						{
							sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);
						}

						return;
					}
				}

				// Southern Zeth'Gor Tower
				if(pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
				{
					GameObject* pSouthern = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-1150.0f, 2110.0f, 84.0f, 300150);
					if(pSouthern != NULL && pPlayer->CalcDistance(pPlayer, pSouthern) < 40)
					{
						pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
						pQuest->SendUpdateAddKill(1);
						pQuest->UpdatePlayerFields();

						GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -1150.53f, 2109.92f, 84.4204f, 0, 4, 0, 0, 0, 0);
						if(pGameobject != NULL)
							sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);

						return;
					}
				}

				// Forge Zeth'Gor Tower
				if(pQuest->GetMobCount(2) < pQuest->GetQuest()->required_mobcount[2])
				{
					GameObject* pForge = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-893.0f, 1919.0f, 82.0f, 300150);
					if(pForge != NULL && pPlayer->CalcDistance(pPlayer, pForge) < 40)
					{
						pQuest->SetMobCount(2, pQuest->GetMobCount(2) + 1);
						pQuest->SendUpdateAddKill(2);
						pQuest->UpdatePlayerFields();

						GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -893.499f, 1919.27f, 81.6449f, 0, 4, 0, 0, 0, 0);
						if(pGameobject != NULL)
							sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);

						return;
					}
				}

				// Foothill Zeth'Gor Tower
				if(pQuest->GetMobCount(3) < pQuest->GetQuest()->required_mobcount[3])
				{
					GameObject* pFoothill = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-978.0f, 1879.0f, 111.0f, 300150);
					if(pFoothill != NULL && pPlayer->CalcDistance(pPlayer, pFoothill) < 40)
					{
						pQuest->SetMobCount(3, pQuest->GetMobCount(3) + 1);
						pQuest->SendUpdateAddKill(3);
						pQuest->UpdatePlayerFields();

						GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -977.713f, 1879.500f, 110.892f, 0, 4, 0, 0, 0, 0);
						if(pGameobject != NULL)
							sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);

						return;
					}
				}
				else
					pPlayer->BroadcastMessage("You are to far away!");

			}
			else
				pPlayer->BroadcastMessage("Missing required quest : Zeth'Gor Must Burn");
		}
};




class PrisonerGossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			int32 i = -1;
			Creature* pPrisoner = TO_CREATURE(pObject);
			switch(pPrisoner->GetEntry())
			{
				case 20677: i = 0; break;
				case 20678: i = 1; break;
				case 20679: i = 2; break;
			}

			if(i == -1)
				return;

			QuestLogEntry* pQuest = plr->GetQuestLogForEntry(10368);
			if(pQuest != NULL && pQuest->GetMobCount(i) < pQuest->GetQuest()->required_mobcount[i] && plr->GetItemInterface()->GetItemCount(29501) > 0)
				Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 10104, plr, 1, Arcemu::Gossip::ICON_CHAT, "Walk free, Elder. Bring the spirits back to your tribe.");
		}

		void OnSelectOption(Object* pObject, Player* pPlayer, uint32 Id, const char* EnteredCode)
		{
			switch(Id)
			{
				case 0: OnHello(pObject, pPlayer); break;
				case 1:
					{
						int32 i = -1;
						Creature* pPrisoner = TO_CREATURE(pObject);
						switch(pPrisoner->GetEntry())
						{
							case 20677: i = 0; break;
							case 20678: i = 1; break;
							case 20679: i = 2; break;
						}

						if(i == -1)
							return;

						QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10368);
						if(pQuest != NULL && pQuest->GetMobCount(i) < pQuest->GetQuest()->required_mobcount[i])
						{
							pQuest->SetMobCount(i, pQuest->GetMobCount(i) + 1);
							pQuest->SendUpdateAddKill(i);
							pQuest->UpdatePlayerFields();

							pPrisoner->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You've freed me! The winds speak to my people one again and grant us their strength. I thank you, stranger.");
							pPrisoner->Despawn(5000, 6 * 60 * 1000);
							pPrisoner->SetStandState(STANDSTATE_STAND);
						}
					}
					break;
			}
		}

};

/*--------------------------------------------------------------------------------------------------------*/
class AncestralSpiritWolf : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(AncestralSpiritWolf);
		AncestralSpiritWolf(Creature* c) : CreatureAIScript(c) {}
		void OnLoad()
		{
			_unit->CastSpell(_unit, 29938, false);
		}
};


/*--------------------------------------------------------------------------------------------------------*/

class HellfireDeadNPC : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(HellfireDeadNPC);
		HellfireDeadNPC(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->SetStandState(7);
			_unit->setDeathState(CORPSE);
			_unit->GetAIInterface()->m_canMove = false;
		}
};

class DarkTidingsAlliance : public QuestScript
{
	public:
		void OnQuestComplete(Player* pPlayer, QuestLogEntry* qLogEntry)
		{
			Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17479);
			if(pCreature == NULL)
				return;

			char msg[100];
			sprintf(msg, "Psst, %s, get over here.", pPlayer->GetName());
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, msg);	// Changed Player to Creature. I wonder if it was blizzlike
		}
};

class DarkTidingsHorde : public QuestScript
{
	public:
		void OnQuestComplete(Player* pPlayer, QuestLogEntry* qLogEntry)
		{
			Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17558);
			if(pCreature == NULL)
				return;

			char msg[100];
			sprintf(msg, "Psst, %s, get over here.", pPlayer->GetName());
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, msg);
		}
};

class TracyProudwell_Gossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			menu.AddItem(Arcemu::Gossip::VENDOR, "I have marks to redeem!", 0);
			sQuestMgr.FillQuestMenu(TO_CREATURE(pObject), plr, menu);
			if(plr->HasQuest(5126))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I heard that your dog Fei Fei took Klatu's prayer beads...", 1);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			if(Id == 0)
				plr->GetSession()->SendInventoryList(TO_CREATURE(pObject));
			else if(Id == 1)
				Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 10104, plr, 2, Arcemu::Gossip::ICON_CHAT, "<back>");
			else if(Id == 2)
				OnHello(pObject, plr);
		}
};

void SetupHellfirePeninsula(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(181606, &HaaleshiAltar::Create);
	mgr->register_gameobject_script(184661, &ZethGorMustBurnAlliance::Create);
	mgr->register_creature_gossip(20677, new PrisonerGossip);
	mgr->register_creature_gossip(20678, new PrisonerGossip);
	mgr->register_creature_gossip(20679, new PrisonerGossip);
	mgr->register_quest_script(9587, new DarkTidingsAlliance);
	mgr->register_quest_script(9588, new DarkTidingsHorde);
	mgr->register_creature_script(17077, &AncestralSpiritWolf::Create);
	mgr->register_creature_gossip(18266, new TracyProudwell_Gossip);
}
