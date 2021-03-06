/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"
class FireNova : public Spell
{
	SPELL_FACTORY_FUNCTION(FireNova);
		uint8 CanCast(bool tolerate)
		{
			/*if(p_caster && !p_caster->GetSession()->HasPermissions())
			{
				SendCustomError(SPELL_CUSTOM_ERROR_GM_ONLY);
				return SPELL_FAILED_CUSTOM_ERROR;
			}*/

			uint8 result = Spell::CanCast(tolerate);

			if(result == SPELL_CANCAST_OK)
			{
				if(u_caster)
				{
					int totem_ids[3] = {3903, 3902, 2523};
					Unit * totem;
					for (int i = 0; i < 3; i++)
					{
						totem = u_caster->summonhandler.GetSummonWithEntry(totem_ids[i]); // fire totem rank 1
						if (totem != NULL)
							return result;
					}
					if(totem == NULL)
					{
						SendCustomError(SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM); // does not appear to be sending a message to client
						result = SPELL_FAILED_CUSTOM_ERROR;
					}
				}
			}

			return result;
		}
		void SpellEffectDummy(uint32 i)
		{
			int totem_ids[3] = {3903, 3902, 2523};
			Unit * totem;
			for (int i = 0; i < 3; i++)
			{
				totem = u_caster->summonhandler.GetSummonWithEntry(totem_ids[i]); // fire totem rank 1
				if (totem != NULL)
					break;
			}
			if(totem == NULL)
			{
				SendCustomError(SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM);
				return;
			}

			totem->CastSpellAoF(totem->GetPositionX(), totem->GetPositionY(), totem->GetPositionZ(), dbcSpell.LookupEntryForced(8349), true);
			//totem->CastSpell(totem, 8349, true);
		}
};

void SpellFactoryMgr::SetupShaman()
{
	AddSpellById(1535, FireNova::Create);
}
