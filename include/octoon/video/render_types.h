#ifndef OCTOON_RENDER_TYPES_H_
#define OCTOON_RENDER_TYPES_H_

#include <octoon/math/math.h>
#include <octoon/runtime/rtti.h>
#include <octoon/runtime/rtti_interface.h>

namespace octoon
{
	namespace video
	{
		typedef std::shared_ptr<class Camera> CameraPtr;
		typedef std::shared_ptr<class Mesh> MeshPtr;
		typedef std::shared_ptr<class Geometry> GeometryPtr;
		typedef std::shared_ptr<class Material> MaterialPtr;
		typedef std::shared_ptr<class RenderObject> RenderObjectPtr;
		typedef std::shared_ptr<class RenderScene> RenderScenePtr;
		typedef std::unique_ptr<class TextContour> TextContourPtr;
		typedef std::shared_ptr<class TextContourGroup> TextContourGroupPtr;
		typedef std::shared_ptr<class TextFile> TextFilePtr;
		typedef std::shared_ptr<class TextMaterial> TextMaterialPtr;
		typedef std::shared_ptr<class TextMeshing> TextMeshingPtr;

		typedef std::vector<TextFilePtr> TextFiles;
		typedef std::vector<TextMaterialPtr> TextMaterials;
		typedef std::vector<TextContourPtr> TextContours;
		typedef std::vector<TextContourGroupPtr> TextContourGroups;
		typedef std::vector<RenderScene*> RenderScenes;
		typedef std::vector<Camera*> CameraRaws;
		typedef std::vector<RenderObject*> RenderObjectRaws;

		enum class CameraType
		{
			Ortho,
			Perspective
		};

		enum class GraphicsIndexType
		{
			Uint16,
			Uint32,
		};

		enum class DrawType
		{
			Points,
			Lines,
			Triangles
		};

		struct TextColor
		{
			enum Type
			{
				FrontColor,
				SideColor,
				BeginRange_ = FrontColor,
				EndRange_ = SideColor,
				RangeSize_ = (EndRange_ - BeginRange_) + 1,
			};
		};

		enum class TextShaingMode
		{
			PureColor,
		};

		typedef std::uint32_t TextColors;
	}
}

#endif