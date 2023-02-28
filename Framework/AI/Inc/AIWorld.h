#pragma once

namespace AI
{
	class Entity;
	using EntityPtrs = std::vector<Entity*>;

	class AIWorld
	{
	public:
		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		std::vector<Entity*> GetAllEntitiesOfType(uint32_t typeID);

		uint32_t GetNextID() const
		{
			return mNextId++;
		}

	private:
		EntityPtrs mEntities;
		mutable uint32_t mNextId = 0;
	};
}