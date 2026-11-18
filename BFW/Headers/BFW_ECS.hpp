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

			void SetType(const uint8_t _Type);

			const uint8_t GetType() const;

			LightComponent& operator= (const LightComponent& _Other);
			LightComponent& operator= (LightComponent&& _Other) noexcept;

		private:

			friend SafePointer<LightComponent>;

			mutable Vector<SafePointer<LightComponent>*> SafePointers;

			uint8_t Type;

		};

		class BFW_API Entity
		{

		public:

			TransformComponent Transform;

			Entity();
			Entity(const Entity& _Other);
			Entity(Entity&& _Other) noexcept;
			~Entity();

			void SetCurrentScene(Scene* _CurrentScene);

			const bool SetName(const BFW_STRING_VIEW_TYPE& _Name);

			void AddTag(const BFW_STRING_VIEW_TYPE& _Tag);
			void RemoveTag(const BFW_STRING_VIEW_TYPE& _Tag);
			void ClearTags();

			void SetParent(Entity* _Parent);

			void PushChild(const Entity& _Child);
			void EmplaceChild(Entity&& _Child) noexcept;
			void EraseChild(const size_t _Index);
			void ClearChildren();

			void AddCameraComponent(const CameraComponent& _Component = CameraComponent());
			void AddLightComponent(const LightComponent& _Component = LightComponent());

			void RemoveCameraComponent();
			void RemoveLightComponent();

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

		};

		class BFW_API Scene
		{

		public:

			Scene();
			Scene(const Scene& _Other);
			Scene(Scene&& _Other) noexcept;
			~Scene();



			Scene& operator= (const Scene& _Other);
			Scene& operator= (Scene&& _Other) noexcept;

		private:

			friend Entity;

			Vector<Entity> Entities;
			Vector<CameraComponent> CameraComponents;
			Vector<LightComponent> LightComponents;

		};

	}

}



#endif
