#ifndef BFW_ECS_hpp

#define BFW_ECS_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace ECS
	{

		class BFW_API TransformComponent
		{

		public:

			Math::Vec3 Position;
			Math::Vec3 Rotation;
			Math::Vec3 ScaleByX;
			Math::Vec3 ScaleByY;
			Math::Vec3 ScaleByZ;
			Math::Vec3 FlipAxis;

			TransformComponent();
			TransformComponent(const TransformComponent& _Other);
			TransformComponent(TransformComponent&& _Other) noexcept;
			~TransformComponent();

			const bool Deserialize(const Assets::Json& _Json);

			const Assets::Json Serialize() const;

			const Math::Mat4 Model(const Entity* _Parent) const;

			TransformComponent& operator= (const TransformComponent& _Other);
			TransformComponent& operator= (TransformComponent&& _Other) noexcept;

		};

		class BFW_API CameraComponent
		{

		public:

			Math::Vec3 Position;
			Math::Vec3 Rotation;
			float FieldOfView;
			float NearPlane;
			float FarPlane;
			bool Perspective;
			bool XRatioFOV;

			CameraComponent();
			CameraComponent(const CameraComponent& _Other);
			CameraComponent(CameraComponent&& _Other) noexcept;
			~CameraComponent();

			const bool Deserialize(const Assets::Json& _Json);

			const Assets::Json Serialize() const;

			const Math::Mat4 View() const;
			const Math::Mat4 Projection(const float _AspectRatio) const;

			CameraComponent& operator= (const CameraComponent& _Other);
			CameraComponent& operator= (CameraComponent&& _Other) noexcept;

		private:

			friend SafePointer<CameraComponent>;

			mutable Vector<SafePointer<CameraComponent>*> SafePointers;

		};

		enum BFW_API LightTypes : const uint8_t
		{
			_PointLightType = 0,
			_SpotLightType = 1,
			_DirectionalLightType = 2
		};

		class BFW_API LightComponent
		{

		public:

			Math::Vec3 Color;
			float Intensity;
			Math::Vec3 Direction;
			float ThetaCone;
			float ThetaFade;

			LightComponent();
			LightComponent(const LightComponent& _Other);
			LightComponent(LightComponent&& _Other) noexcept;
			~LightComponent();

			const bool Deserialize(const Assets::Json& _Json);

			void SetType(const uint8_t _Type);

			const Assets::Json Serialize() const;

			const uint8_t GetType() const;

			LightComponent& operator= (const LightComponent& _Other);
			LightComponent& operator= (LightComponent&& _Other) noexcept;

		private:

			friend SafePointer<LightComponent>;

			mutable Vector<SafePointer<LightComponent>*> SafePointers;

			uint8_t Type;

		};

		class BFW_API ScriptComponent
		{

		public:

			ScriptComponent();
			ScriptComponent(const ScriptComponent& _Other);
			ScriptComponent(ScriptComponent&& _Other) noexcept;
			~ScriptComponent();

			const bool Deserialize(const Assets::Json& _Json);

			void SetScript(const BFW_STRING_VIEW_TYPE& _ScriptLibName, const SharedPointer<Assets::ScriptLib> _ScriptLib, const BFW_STRING_VIEW_TYPE& _NameSpace);

			void OnSetup(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene);
			void OnUpdate(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene);
			void OnLateUpdate(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene);
			void OnFixedUpdate(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene);
			void OnRender(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene);
			void OnStop(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene);

			const Assets::Json Serialize() const;

			const BFW_STRING_TYPE& GetScriptLibName() const;
			const BFW_STRING_TYPE& GetNameSpace() const;
			const Assets::Json& GetSerializedData() const;

			ScriptComponent& operator= (const ScriptComponent& _Other);
			ScriptComponent& operator= (ScriptComponent&& _Other) noexcept;

		private:

			friend SafePointer<ScriptComponent>;

			mutable Vector<SafePointer<ScriptComponent>*> SafePointers;

			BFW_STRING_TYPE ScriptLibName;
			SharedPointer<Assets::ScriptLib> ScriptLib;
			BFW_STRING_TYPE NameSpace;

			Assets::Json Object;
			Assets::Json SerializedData;

		};

		class BFW_API Entity
		{

		public:

			TransformComponent Transform;

			Entity();
			Entity(const Entity& _Other);
			Entity(Entity&& _Other) noexcept;
			~Entity();

			const bool Deserialize(const Assets::Json& _Json);

			void SetCurrentScene(Scene* _CurrentScene);

			const bool SetName(const BFW_STRING_VIEW_TYPE& _Name);

			void AddTag(const BFW_STRING_VIEW_TYPE& _Tag);
			void RemoveTag(const BFW_STRING_VIEW_TYPE& _Tag);
			void ClearTags();

			void SetParent(Entity* _Parent);

			Entity& PushChild(const Entity& _Child);
			Entity& EmplaceChild(Entity&& _Child);
			void EraseChild(const size_t _Index);
			void ClearChildren();

			CameraComponent& AddCameraComponent(const CameraComponent& _Component = CameraComponent());
			LightComponent& AddLightComponent(const LightComponent& _Component = LightComponent());
			ScriptComponent& AddScriptComponent(const ScriptComponent& _Component = ScriptComponent());

			void RemoveCameraComponent();
			void RemoveLightComponent();
			void RemoveScriptComponent();

			const Assets::Json Serialize() const;

			const bool HasTag(const BFW_STRING_VIEW_TYPE& _Tag) const;

			Scene* GetCurrentScene();
			const Scene* GetCurrentScene() const;
			const BFW_STRING_TYPE& GetGUID() const;
			const BFW_STRING_TYPE& GetName() const;
			const Vector<BFW_STRING_TYPE>& GetTagsList() const;
			Entity* GetParent();
			const Entity* GetParent() const;
			const size_t GetChildrenSize() const;
			Entity& GetChild(const size_t _Index);
			const Entity& GetChild(const size_t _Index) const;
			SafePointer<CameraComponent> GetCamera();
			const SafePointer<CameraComponent> GetCamera() const;
			SafePointer<LightComponent> GetLight();
			const SafePointer<LightComponent> GetLight() const;
			SafePointer<ScriptComponent> GetScript();
			const SafePointer<ScriptComponent> GetScript() const;

			Entity& operator= (const Entity& _Other);
			Entity& operator= (Entity&& _Other) noexcept;

		private:

			friend SafePointer<Entity>;

			mutable Vector<SafePointer<Entity>*> SafePointers;

			Scene* CurrentScene;
			BFW_STRING_TYPE GUID;
			BFW_STRING_TYPE Name;
			Vector<BFW_STRING_TYPE> TagsList;
			Trie<bool> Tags;
			SafePointer<Entity> Parent;
			Vector<Entity> Children;
			SafePointer<CameraComponent> Camera;
			SafePointer<LightComponent> Light;
			SafePointer<ScriptComponent> Script;

		};

		class BFW_API Scene
		{

		public:

			Scene();
			Scene(const Scene& _Other);
			Scene(Scene&& _Other) noexcept;
			~Scene();

			const bool Deserialize(const Assets::Json& _Json);

			const bool Setup(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Vector<BFW_STRING_TYPE>& _Warnings);
			void Update(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Vector<BFW_STRING_TYPE>& _Warnings);
			void LateUpdate(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Vector<BFW_STRING_TYPE>& _Warnings);
			void FixedUpdate(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Vector<BFW_STRING_TYPE>& _Warnings);
			void Render(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Vector<BFW_STRING_TYPE>& _Warnings);
			void Stop(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Vector<BFW_STRING_TYPE>& _Warnings);

			Entity& Add(Entity* _Parent = nullptr);
			Entity& Add(const Entity& _Entity, Entity* _Parent = nullptr);
			Entity& Add(Entity&& _Entity, Entity* _Parent = nullptr);
			Entity* AddPrefab(const Assets::Json& _Json, Entity* _Parent = nullptr);

			void Remove(const size_t _Index);
			void Remove(const BFW_STRING_VIEW_TYPE& _GUID);
			void Remove(const Entity* _Entity);

			void Clear();

			const bool SetName(const BFW_STRING_VIEW_TYPE& _Name);

			void SetActiveCamera(const CameraComponent* _ActiveCamera);

			const Assets::Json Serialize() const;

			Entity* Find(const BFW_STRING_VIEW_TYPE& _GUID);
			const Entity* Find(const BFW_STRING_VIEW_TYPE& _GUID) const;
			Entity* FindByName(const BFW_STRING_VIEW_TYPE& _Name);
			const Entity* FindByName(const BFW_STRING_VIEW_TYPE& _Name) const;
			const Vector<Entity*> FindByTag(const BFW_STRING_VIEW_TYPE& _Tag);
			const Vector<const Entity*> FindByTag(const BFW_STRING_VIEW_TYPE& _Tag) const;

			const bool Contains(const Entity* _Entity) const;
			const bool Contains(const BFW_STRING_VIEW_TYPE& _GUID) const;

			const BFW_STRING_TYPE& GetGUID() const;
			const BFW_STRING_TYPE& GetName() const;

			CameraComponent* GetActiveCamera();
			const CameraComponent* GetActiveCamera() const;

			const size_t GetTotalCount() const;
			const size_t GetRootCount() const;
			Entity& GetEntity(const size_t _Index);
			const Entity& GetEntity(const size_t _Index) const;

			Scene& operator= (const Scene& _Other);
			Scene& operator= (Scene&& _Other) noexcept;

		private:

			friend Entity;

			BFW_STRING_TYPE GUID;
			BFW_STRING_TYPE Name;

			Vector<Entity> Entities;
			Vector<CameraComponent> CameraComponents;
			Vector<LightComponent> LightComponents;
			Vector<ScriptComponent> ScriptComponents;

			Vector<Entity> SpawnQueue;
			Vector<SafePointer<Entity>> DespawnQueue;

			SafePointer<CameraComponent> ActiveCamera;

		};

	}

}



#endif
