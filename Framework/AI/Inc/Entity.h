#pragma once


namespace AI
{
	class AIWorld;
	class Entity
	{
	public:
		Entity(AIWorld& _world, uint32_t typeId);
		virtual ~Entity();

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(Entity&&) = delete;

		AIWorld& world;
		float posX = 0.f;
		float posY = 0.f;
		float headingX = 0.f;
		float headingY = 1.f;
		float radius = 1.f;

		uint32_t GetTypeID() const { return static_cast<uint32_t>(mUniqueID >> 32); }
		uint64_t GetUniqueID() const { return mUniqueID; }
	private:
		const uint64_t mUniqueID = 0;
	};
}