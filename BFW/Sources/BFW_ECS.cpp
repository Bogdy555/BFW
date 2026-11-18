#include "../Headers/BFW.hpp"



template <typename T> static const bool EntityAddComponent(BFW::Vector<T>& _Components, BFW::SafePointer<T>& _Component, const T& _NewComponent)
{
	if ((T*)(_Component))
	{
		*_Component = _NewComponent;
		return true;
	}

	_Component = &_Components.PushBack(_NewComponent);

	return true;
}

template <typename T> static const bool EntityRemoveComponent(BFW::Vector<T>& _Components, BFW::SafePointer<T>& _Component)
{
	for (size_t _Index = 0; _Index < _Components.GetSize(); _Index++)
	{
		if (&_Components[_Index] == (T*)(_Component))
		{
			_Components.Erase(_Index);
			return true;
		}
	}

	_Component = nullptr;

	return false;
}



BFW::ECS::TransformComponent::TransformComponent() : Position(), Rotation(), ScaleByX(Math::Vec3(1.0f, 0.0f, 0.0f)), ScaleByY(Math::Vec3(0.0f, 1.0f, 0.0f)), ScaleByZ(Math::Vec3(0.0f, 0.0f, 1.0f)), FlipAxis()
{

}

BFW::ECS::TransformComponent::TransformComponent(const TransformComponent& _Other) : Position(_Other.Position), Rotation(_Other.Rotation), ScaleByX(_Other.ScaleByX), ScaleByY(_Other.ScaleByY), ScaleByZ(_Other.ScaleByZ), FlipAxis(_Other.FlipAxis)
{

}

BFW::ECS::TransformComponent::TransformComponent(TransformComponent&& _Other) noexcept : Position((Math::Vec3&&)(_Other.Position)), Rotation((Math::Vec3&&)(_Other.Rotation)), ScaleByX((Math::Vec3&&)(_Other.ScaleByX)), ScaleByY((Math::Vec3&&)(_Other.ScaleByY)), ScaleByZ((Math::Vec3&&)(_Other.ScaleByZ)), FlipAxis((Math::Vec3&&)(_Other.FlipAxis))
{

}

BFW::ECS::TransformComponent::~TransformComponent()
{

}

const BFW::Math::Mat4 BFW::ECS::TransformComponent::Model(const Entity* _Parent) const
{
	if (_Parent)
	{
		return
			_Parent->Transform.Model(_Parent->GetParent()) *
			Math::Mat4::GetTranslation(Position) *
			Math::Mat4::GetRotation(Rotation.y, Math::Vec3(0.0f, 1.0f, 0.0f)) *
			Math::Mat4::GetRotation(Rotation.x, Math::Vec3(1.0f, 0.0f, 0.0f)) *
			Math::Mat4::GetRotation(Rotation.z, Math::Vec3(0.0f, 0.0f, 1.0f)) *
			Math::Mat4(ScaleByX, ScaleByY, ScaleByZ) *
			Math::Mat4::GetFlip(FlipAxis);
	}

	return
		Math::Mat4::GetTranslation(Position) *
		Math::Mat4::GetRotation(Rotation.y, Math::Vec3(0.0f, 1.0f, 0.0f)) *
		Math::Mat4::GetRotation(Rotation.x, Math::Vec3(1.0f, 0.0f, 0.0f)) *
		Math::Mat4::GetRotation(Rotation.z, Math::Vec3(0.0f, 0.0f, 1.0f)) *
		Math::Mat4(ScaleByX, ScaleByY, ScaleByZ) *
		Math::Mat4::GetFlip(FlipAxis);
}

BFW::ECS::TransformComponent& BFW::ECS::TransformComponent::operator= (const TransformComponent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = _Other.Position;
	Rotation = _Other.Rotation;
	ScaleByX = _Other.ScaleByX;
	ScaleByY = _Other.ScaleByY;
	ScaleByZ = _Other.ScaleByZ;
	FlipAxis = _Other.FlipAxis;

	return *this;
}

BFW::ECS::TransformComponent& BFW::ECS::TransformComponent::operator= (TransformComponent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = (Math::Vec3&&)(_Other.Position);
	Rotation = (Math::Vec3&&)(_Other.Rotation);
	ScaleByX = (Math::Vec3&&)(_Other.ScaleByX);
	ScaleByY = (Math::Vec3&&)(_Other.ScaleByY);
	ScaleByZ = (Math::Vec3&&)(_Other.ScaleByZ);
	FlipAxis = (Math::Vec3&&)(_Other.FlipAxis);

	return *this;
}



BFW::ECS::CameraComponent::CameraComponent() : Position(), Rotation(), FieldOfView(90.0f), NearPlane(0.001f), FarPlane(1000.0f), Perspective(true), XRatioFOV(false), SafePointers()
{

}

BFW::ECS::CameraComponent::CameraComponent(const CameraComponent& _Other) : Position(_Other.Position), Rotation(_Other.Rotation), FieldOfView(_Other.FieldOfView), NearPlane(_Other.NearPlane), FarPlane(_Other.FarPlane), Perspective(_Other.Perspective), XRatioFOV(_Other.XRatioFOV), SafePointers()
{

}

BFW::ECS::CameraComponent::CameraComponent(CameraComponent&& _Other) noexcept : Position((Math::Vec3&&)(_Other.Position)), Rotation((Math::Vec3&&)(_Other.Rotation)), FieldOfView(_Other.FieldOfView), NearPlane(_Other.NearPlane), FarPlane(_Other.FarPlane), Perspective(_Other.Perspective), XRatioFOV(_Other.XRatioFOV), SafePointers()
{
	SafePointer<CameraComponent>::MoveAll(this, &_Other);

	_Other.FieldOfView = 90.0f;
	_Other.NearPlane = 0.001f;
	_Other.FarPlane = 1000.0f;
	_Other.Perspective = true;
	_Other.XRatioFOV = false;
}

BFW::ECS::CameraComponent::~CameraComponent()
{
	SafePointer<CameraComponent>::ReleaseAll(this);
}

const BFW::Math::Mat4 BFW::ECS::CameraComponent::View() const
{
	return
		Math::Mat4::GetRotation(-Rotation.z, Math::Vec3(0.0f, 0.0f, 1.0f)) *
		Math::Mat4::GetRotation(-Rotation.x, Math::Vec3(1.0f, 0.0f, 0.0f)) *
		Math::Mat4::GetRotation(-Rotation.y, Math::Vec3(0.0f, 1.0f, 0.0f)) *
		Math::Mat4::GetTranslation(-Position);
}

const BFW::Math::Mat4 BFW::ECS::CameraComponent::Projection(const float _AspectRatio) const
{
	if (Perspective)
	{
		if (XRatioFOV)
		{
			return Math::Mat4::GetPerspectiveOxRightHand(FieldOfView, _AspectRatio, NearPlane, FarPlane);
		}

		return Math::Mat4::GetPerspectiveOyRightHand(FieldOfView, _AspectRatio, NearPlane, FarPlane);
	}

	if (XRatioFOV)
	{
		return Math::Mat4::GetOrthoRightHand(-FieldOfView / 2.0f, FieldOfView / 2.0f, -FieldOfView / 2.0f / _AspectRatio, FieldOfView / 2.0f / _AspectRatio, NearPlane, FarPlane);
	}

	return Math::Mat4::GetOrthoRightHand(-FieldOfView / 2.0f * _AspectRatio, FieldOfView / 2.0f * _AspectRatio, -FieldOfView / 2.0f, FieldOfView / 2.0f, NearPlane, FarPlane);
}

BFW::ECS::CameraComponent& BFW::ECS::CameraComponent::operator= (const CameraComponent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = _Other.Position;
	Rotation = _Other.Rotation;
	FieldOfView = _Other.FieldOfView;
	NearPlane = _Other.NearPlane;
	FarPlane = _Other.FarPlane;
	Perspective = _Other.Perspective;
	XRatioFOV = _Other.XRatioFOV;

	return *this;
}

BFW::ECS::CameraComponent& BFW::ECS::CameraComponent::operator= (CameraComponent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	SafePointer<CameraComponent>::MoveAll(this, &_Other);

	Position = (Math::Vec3&&)(_Other.Position);
	Rotation = (Math::Vec3&&)(_Other.Rotation);
	FieldOfView = _Other.FieldOfView;
	NearPlane = _Other.NearPlane;
	FarPlane = _Other.FarPlane;
	Perspective = _Other.Perspective;
	XRatioFOV = _Other.XRatioFOV;

	_Other.FieldOfView = 90.0f;
	_Other.NearPlane = 0.001f;
	_Other.FarPlane = 1000.0f;
	_Other.Perspective = true;
	_Other.XRatioFOV = false;

	return *this;
}



BFW::ECS::LightComponent::LightComponent() : Color(Math::Vec3(1.0f, 1.0f, 1.0f)), Intensity(1.0f), Direction(), ThetaCone(0.0f), ThetaFade(0.0f), SafePointers(), Type(_PointLightType)
{

}

BFW::ECS::LightComponent::LightComponent(const LightComponent& _Other) : Color(_Other.Color), Intensity(_Other.Intensity), Direction(_Other.Direction), ThetaCone(_Other.ThetaCone), ThetaFade(_Other.ThetaFade), SafePointers(), Type(_Other.Type)
{

}

BFW::ECS::LightComponent::LightComponent(LightComponent&& _Other) noexcept : Color(_Other.Color), Intensity(_Other.Intensity), Direction((Math::Vec3&&)(_Other.Direction)), ThetaCone(_Other.ThetaCone), ThetaFade(_Other.ThetaFade), SafePointers(), Type(_Other.Type)
{
	SafePointer<LightComponent>::MoveAll(this, &_Other);

	_Other.Color = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Intensity = 1.0f;
	_Other.ThetaCone = 0.0f;
	_Other.ThetaFade = 0.0f;
	_Other.Type = _PointLightType;
}

BFW::ECS::LightComponent::~LightComponent()
{
	SafePointer<LightComponent>::ReleaseAll(this);
}

void BFW::ECS::LightComponent::SetType(const uint8_t _Type)
{
	if (_Type > 2)
	{
		throw nullptr;
	}

	Type = _Type;
}

const uint8_t BFW::ECS::LightComponent::GetType() const
{
	return Type;
}

BFW::ECS::LightComponent& BFW::ECS::LightComponent::operator= (const LightComponent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Color = _Other.Color;
	Intensity = _Other.Intensity;
	Direction = _Other.Direction;
	ThetaCone = _Other.ThetaCone;
	ThetaFade = _Other.ThetaFade;
	Type = _Other.Type;

	return *this;
}

BFW::ECS::LightComponent& BFW::ECS::LightComponent::operator= (LightComponent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	SafePointer<LightComponent>::MoveAll(this, &_Other);

	Color = _Other.Color;
	Intensity = _Other.Intensity;
	Direction = (Math::Vec3&&)(_Other.Direction);
	ThetaCone = _Other.ThetaCone;
	ThetaFade = _Other.ThetaFade;
	Type = _Other.Type;

	_Other.Color = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Intensity = 1.0f;
	_Other.ThetaCone = 0.0f;
	_Other.ThetaFade = 0.0f;
	_Other.Type = _PointLightType;

	return *this;
}



BFW::ECS::Entity::Entity() : Transform(), SafePointers(), CurrentScene(nullptr), GUID(GUID::GetString()), Name(BFW_STRING_PREFIX("Name")), TagsList(), Tags(), Parent(nullptr), Children(), Camera(), Light()
{

}

BFW::ECS::Entity::Entity(const Entity& _Other) : Transform(_Other.Transform), SafePointers(), CurrentScene(_Other.CurrentScene), GUID(GUID::GetString()), Name(_Other.Name), TagsList(_Other.TagsList), Tags(_Other.Tags), Parent(nullptr), Children(_Other.Children), Camera(), Light()
{
	for (size_t _Index = 0; _Index < Children.GetSize(); _Index++)
	{
		Children[_Index].Parent = this;
	}

	if (!CurrentScene)
	{
		return;
	}

	if ((const CameraComponent*)(_Other.Camera))
	{
		AddCameraComponent(*_Other.Camera);
	}

	if ((const LightComponent*)(_Other.Light))
	{
		AddLightComponent(*_Other.Light);
	}
}

BFW::ECS::Entity::Entity(Entity&& _Other) noexcept : Transform((TransformComponent&&)(_Other.Transform)), SafePointers(), CurrentScene(_Other.CurrentScene), GUID(_Other.GUID), Name(_Other.Name), TagsList((Vector<BFW_STRING_TYPE>&&)(_Other.TagsList)), Tags((Trie<bool>&&)(_Other.Tags)), Parent((SafePointer<Entity>&&)(_Other.Parent)), Children((Vector<Entity>&&)(_Other.Children)), Camera((SafePointer<CameraComponent>&&)(_Other.Camera)), Light((SafePointer<LightComponent>&&)(_Other.Light))
{
	SafePointer<Entity>::MoveAll(this, &_Other);

	_Other.CurrentScene = nullptr;
	_Other.GUID = GUID::GetString();
	_Other.Name = BFW_STRING_PREFIX("Name");
}

BFW::ECS::Entity::~Entity()
{
	SafePointer<Entity>::ReleaseAll(this);

	GUID::ReleaseString(GUID);
	RemoveCameraComponent();
	RemoveLightComponent();
}

void BFW::ECS::Entity::SetCurrentScene(Scene* _CurrentScene)
{
	if (CurrentScene == _CurrentScene)
	{
		return;
	}

	bool _HasCameraComponent = (CameraComponent*)(Camera) != nullptr;
	CameraComponent _Camera;
	bool _HasLightComponent = (LightComponent*)(Light) != nullptr;
	LightComponent _Light;

	if (_HasCameraComponent)
	{
		_Camera = *Camera;
	}

	if (_HasLightComponent)
	{
		_Light = *Light;
	}

	RemoveCameraComponent();
	RemoveLightComponent();

	CurrentScene = _CurrentScene;

	if (_HasCameraComponent)
	{
		AddCameraComponent(_Camera);
	}

	if (_HasLightComponent)
	{
		AddLightComponent(_Light);
	}

	Parent = nullptr;

	for (size_t _Index = 0; _Index < Children.GetSize(); _Index++)
	{
		Children[_Index].SetCurrentScene(_CurrentScene);
		Children[_Index].Parent = this;
	}
}

const bool BFW::ECS::Entity::SetName(const BFW_STRING_VIEW_TYPE& _Name)
{
	if (!_Name.size())
	{
		return false;
	}

	Name = _Name;

	return true;
}

void BFW::ECS::Entity::AddTag(const BFW_STRING_VIEW_TYPE& _Tag)
{
	if (_Tag.size() == 0)
	{
		return;
	}

	for (size_t _Index = 0; _Index < TagsList.GetSize(); _Index++)
	{
		if (TagsList[_Index] == _Tag)
		{
			return;
		}
	}

	TagsList.EmplaceBack(BFW_STRING_TYPE(_Tag));
	Tags.Push(BFW_STRING_TYPE(_Tag).c_str(), true);
}

void BFW::ECS::Entity::RemoveTag(const BFW_STRING_VIEW_TYPE& _Tag)
{
	if (_Tag.size() == 0)
	{
		return;
	}

	Tags.Erase(BFW_STRING_TYPE(_Tag).c_str());

	for (size_t _Index = 0; _Index < TagsList.GetSize(); _Index++)
	{
		if (TagsList[_Index] == _Tag)
		{
			TagsList.Erase(_Index);
			return;
		}
	}
}

void BFW::ECS::Entity::ClearTags()
{
	TagsList.Clear();
	Tags = Trie<bool>();
}

void BFW::ECS::Entity::SetParent(Entity* _Parent)
{
	if (_Parent != nullptr && CurrentScene != _Parent->CurrentScene)
	{
		throw nullptr;
	}

	Entity* _Current = _Parent;

	while (_Current)
	{
		if (_Current == this)
		{
			throw nullptr;
		}

		_Current = (Entity*)(_Current->Parent);
	}

	Parent = _Parent;
}

void BFW::ECS::Entity::PushChild(const Entity& _Child)
{
	Children.PushBack(_Child);
	Children[Children.GetSize() - 1].Parent = this;
}

void BFW::ECS::Entity::EmplaceChild(Entity&& _Child) noexcept
{
	Children.EmplaceBack((Entity&&)(_Child));
	Children[Children.GetSize() - 1].Parent = this;
}

void BFW::ECS::Entity::EraseChild(const size_t _Index)
{
	Children.Erase(_Index);
}

void BFW::ECS::Entity::ClearChildren()
{
	Children.Clear();
}

void BFW::ECS::Entity::AddCameraComponent(const CameraComponent& _Component)
{
	if (!CurrentScene || !EntityAddComponent<CameraComponent>(CurrentScene->CameraComponents, Camera, _Component))
	{
		throw nullptr;
	}
}

void BFW::ECS::Entity::AddLightComponent(const LightComponent& _Component)
{
	if (!CurrentScene || !EntityAddComponent<LightComponent>(CurrentScene->LightComponents, Light, _Component))
	{
		throw nullptr;
	}
}

void BFW::ECS::Entity::RemoveCameraComponent()
{
	bool _Removed = !CurrentScene || !(CameraComponent*)(Camera) || EntityRemoveComponent<CameraComponent>(CurrentScene->CameraComponents, Camera);
}

void BFW::ECS::Entity::RemoveLightComponent()
{
	bool _Removed = !CurrentScene || !(LightComponent*)(Light) || EntityRemoveComponent<LightComponent>(CurrentScene->LightComponents, Light);
}

const bool BFW::ECS::Entity::HasTag(const BFW_STRING_VIEW_TYPE& _Tag) const
{
	return Tags.GetData(BFW_STRING_TYPE(_Tag).c_str()) != nullptr;
}

BFW::ECS::Scene* BFW::ECS::Entity::GetCurrentScene()
{
	return CurrentScene;
}

const BFW::ECS::Scene* BFW::ECS::Entity::GetCurrentScene() const
{
	return CurrentScene;
}

const BFW_STRING_TYPE& BFW::ECS::Entity::GetGUID() const
{
	return GUID;
}

const BFW_STRING_TYPE& BFW::ECS::Entity::GetName() const
{
	return Name;
}

const BFW::Vector<BFW_STRING_TYPE>& BFW::ECS::Entity::GetTagsList() const
{
	return TagsList;
}

BFW::ECS::Entity* BFW::ECS::Entity::GetParent()
{
	return (Entity*)(Parent);
}

const BFW::ECS::Entity* BFW::ECS::Entity::GetParent() const
{
	return (const Entity*)(Parent);
}

const size_t BFW::ECS::Entity::GetChildrenSize() const
{
	return Children.GetSize();
}

BFW::ECS::Entity& BFW::ECS::Entity::GetChild(const size_t _Index)
{
	return Children[_Index];
}

const BFW::ECS::Entity& BFW::ECS::Entity::GetChild(const size_t _Index) const
{
	return Children[_Index];
}

BFW::SafePointer<BFW::ECS::CameraComponent> BFW::ECS::Entity::GetCamera()
{
	return Camera;
}

const BFW::SafePointer<BFW::ECS::CameraComponent> BFW::ECS::Entity::GetCamera() const
{
	return Camera;
}

BFW::SafePointer<BFW::ECS::LightComponent> BFW::ECS::Entity::GetLight()
{
	return Light;
}

const BFW::SafePointer<BFW::ECS::LightComponent> BFW::ECS::Entity::GetLight() const
{
	return Light;
}

BFW::ECS::Entity& BFW::ECS::Entity::operator= (const Entity& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	GUID::ReleaseString(GUID);
	RemoveCameraComponent();
	RemoveLightComponent();

	Transform = _Other.Transform;
	CurrentScene = _Other.CurrentScene;
	GUID = GUID::GetString();
	Name = _Other.Name;
	TagsList = _Other.TagsList;
	Tags = _Other.Tags;
	Parent = nullptr;
	Children = _Other.Children;

	for (size_t _Index = 0; _Index < Children.GetSize(); _Index++)
	{
		Children[_Index].Parent = this;
	}

	if (!CurrentScene)
	{
		return *this;
	}

	if ((const CameraComponent*)(_Other.Camera))
	{
		AddCameraComponent(*_Other.Camera);
	}

	if ((const LightComponent*)(_Other.Light))
	{
		AddLightComponent(*_Other.Light);
	}

	return *this;
}

BFW::ECS::Entity& BFW::ECS::Entity::operator= (Entity&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	GUID::ReleaseString(GUID);
	RemoveCameraComponent();
	RemoveLightComponent();

	SafePointer<Entity>::MoveAll(this, &_Other);

	Transform = (TransformComponent&&)(_Other.Transform);
	CurrentScene = _Other.CurrentScene;
	GUID = _Other.GUID;
	Name = _Other.Name;
	TagsList = (Vector<BFW_STRING_TYPE>&&)(_Other.TagsList);
	Tags = (Trie<bool>&&)(_Other.Tags);
	Parent = (SafePointer<Entity>&&)(_Other.Parent);
	Children = (Vector<Entity>&&)(_Other.Children);
	Camera = (SafePointer<CameraComponent>&&)(_Other.Camera);
	Light = (SafePointer<LightComponent>&&)(_Other.Light);

	_Other.CurrentScene = nullptr;
	_Other.GUID = GUID::GetString();
	_Other.Name = BFW_STRING_PREFIX("Name");

	return *this;
}



BFW::ECS::Scene::Scene()
{

}

BFW::ECS::Scene::Scene(const Scene& _Other)
{

}

BFW::ECS::Scene::Scene(Scene&& _Other) noexcept
{

}

BFW::ECS::Scene::~Scene()
{
	// vezi ca e delicat aici cu care moare primul
}

BFW::ECS::Scene& BFW::ECS::Scene::operator= (const Scene& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}



	return *this;
}

BFW::ECS::Scene& BFW::ECS::Scene::operator= (Scene&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}



	return *this;
}
