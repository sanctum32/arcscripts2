/*
 * WhyScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2010 WhyDB Team <http://www.whydb.org/>
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

class TheFallenExarch : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(TheFallenExarch)
	TheFallenExarch(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player *pPlayer)
	{
		if( pPlayer->HasQuest(10915) )
			sEAS.SpawnCreature( pPlayer, 22452, -3365.9f, 5143.19f, -9.00132f, 3.05f, DESPAWN_TIME );
	}
};

class TerokksDownfall : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(TerokksDownfall)
	TerokksDownfall(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player *pPlayer)
	{
		pPlayer->CastSpell( pPlayer, 41004, false );
	}
};

void SetupTerokkarForestGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 184999, &TheFallenExarch::Create );	// Auchenai Coffin
	mgr->register_gameobject_script( 185928, &TerokksDownfall::Create );	// Ancient Skull Pile
}