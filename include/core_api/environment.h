/****************************************************************************
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef Y_ENVIRON_H
#define Y_ENVIRON_H

#include <yafray_config.h>

#include "params.h"
#include "yafsystem.h"
#include <list>
#include <vector>

__BEGIN_YAFRAY
class light_t;
class material_t;
class volumeHandler_t;
class VolumeRegion;
class texture_t;
class camera_t;
class background_t;
class integrator_t;
class shaderNode_t;
class integrator_t;
class object3d_t;
class imageFilm_t;
class scene_t;
class colorOutput_t;
class progressBar_t;
class imageHandler_t;

class YAFRAYCORE_EXPORT renderEnvironment_t
{
	public:
		void loadPlugins(const std::string &path);
		bool getPluginPath(std::string &path);

		typedef light_t 		*light_factory_t(paraMap_t &,renderEnvironment_t &);
		typedef material_t 		*material_factory_t(paraMap_t &,std::list<paraMap_t> &, renderEnvironment_t &);
		typedef texture_t 		*texture_factory_t(paraMap_t &,renderEnvironment_t &);
		typedef object3d_t 		*object_factory_t(paraMap_t &,renderEnvironment_t &);
		typedef camera_t 		*camera_factory_t(paraMap_t &,renderEnvironment_t &);
		typedef background_t 	*background_factory_t(paraMap_t &,renderEnvironment_t &);
		typedef integrator_t 	*integrator_factory_t(paraMap_t &,renderEnvironment_t &);
		typedef shaderNode_t 	*shader_factory_t(const paraMap_t &,renderEnvironment_t &);
		typedef volumeHandler_t *volume_factory_t(const paraMap_t &,renderEnvironment_t &);
		typedef VolumeRegion	*volumeregion_factory_t(paraMap_t &,renderEnvironment_t &);
		typedef imageHandler_t	*imagehandler_factory_t(paraMap_t &,renderEnvironment_t &);

		virtual material_t *getMaterial(const std::string &name)const;
		virtual texture_t *getTexture(const std::string &name)const;
		virtual shaderNode_t *getShaderNode(const std::string &name)const;
		camera_t *getCamera(const std::string &name)const;
		shader_factory_t* getShaderNodeFactory(const std::string &name)const;
		background_t* 	getBackground(const std::string &name)const;
		integrator_t* 	getIntegrator(const std::string &name)const;
		scene_t * 		getScene() { return curren_scene; };

		light_t* 		createLight		(const std::string &name, paraMap_t &params);
		texture_t* 		createTexture	(const std::string &name, paraMap_t &params);
		material_t* 	createMaterial	(const std::string &name, paraMap_t &params, std::list<paraMap_t> &eparams);
		object3d_t* 	createObject	(const std::string &name, paraMap_t &params);
		camera_t* 		createCamera	(const std::string &name, paraMap_t &params);
		background_t* 	createBackground(const std::string &name, paraMap_t &params);
		integrator_t* 	createIntegrator(const std::string &name, paraMap_t &params);
		shaderNode_t* 	createShaderNode(const std::string &name, paraMap_t &params);
		volumeHandler_t* createVolumeH(const std::string &name, const paraMap_t &params);
		VolumeRegion*	createVolumeRegion(const std::string &name, paraMap_t &params);
		imageFilm_t*	createImageFilm(const paraMap_t &params, colorOutput_t &output);
		imageHandler_t* createImageHandler(const std::string &name, paraMap_t &params, bool addToTable = true);
		void 			setScene(scene_t *scene) { curren_scene=scene; };
		bool			setupScene(scene_t &scene, const paraMap_t &params, colorOutput_t &output, progressBar_t *pb = 0);
		void clearAll();

		virtual void registerFactory(const std::string &name,light_factory_t *f);
		virtual void registerFactory(const std::string &name,material_factory_t *f);
		virtual void registerFactory(const std::string &name,texture_factory_t *f);
		virtual void registerFactory(const std::string &name,object_factory_t *f);
		virtual void registerFactory(const std::string &name,camera_factory_t *f);
		virtual void registerFactory(const std::string &name,background_factory_t *f);
		virtual void registerFactory(const std::string &name,integrator_factory_t *f);
		virtual void registerFactory(const std::string &name,shader_factory_t *f);
		virtual void registerFactory(const std::string &name,volume_factory_t *f);
		virtual void registerFactory(const std::string &name,volumeregion_factory_t *f);

		virtual void registerImageHandler(const std::string &name, const std::string &validExtensions, const std::string &fullName, imagehandler_factory_t *f);
		virtual std::vector<std::string> listImageHandlers();
		virtual std::vector<std::string> listImageHandlersFullName();
		virtual std::string getImageFormatFromFullName(const std::string &fullname);
		virtual std::string getImageFormatFromExtension(const std::string &extension);
		virtual std::string getImageFullNameFromFormat(const std::string &format);

		int Debug;

		renderEnvironment_t();
		virtual ~renderEnvironment_t();

	protected:
		std::list< sharedlibrary_t > 	pluginHandlers;
		std::map<std::string,light_factory_t *> 	light_factory;
		std::map<std::string,material_factory_t *> 	material_factory;
		std::map<std::string,texture_factory_t *> 	texture_factory;
		std::map<std::string,object_factory_t *> 	object_factory;
		std::map<std::string,camera_factory_t *> 	camera_factory;
		std::map<std::string,background_factory_t *> background_factory;
		std::map<std::string,integrator_factory_t *> integrator_factory;
		std::map<std::string,shader_factory_t *> 	shader_factory;
		std::map<std::string,volume_factory_t *> 	volume_factory;
		std::map<std::string,volumeregion_factory_t *> 	volumeregion_factory;
		std::map<std::string,imagehandler_factory_t *> 	imagehandler_factory;

		std::map<std::string,light_t *> 	light_table;
		std::map<std::string,material_t *> 	material_table;
		std::map<std::string,texture_t *> 	texture_table;
		std::map<std::string,object3d_t *> 	object_table;
		std::map<std::string,camera_t *> 	camera_table;
		std::map<std::string,background_t *> background_table;
		std::map<std::string,integrator_t *> integrator_table;
		std::map<std::string,shaderNode_t *> shader_table;
		std::map<std::string,volumeHandler_t *> volume_table;
		std::map<std::string,VolumeRegion *> volumeregion_table;

		std::map<std::string,imageHandler_t *> imagehandler_table;
		std::map<std::string,std::string> imagehandler_fullnames;
		std::map<std::string,std::string> imagehandler_extensions;
		scene_t *curren_scene;
};

__END_YAFRAY
#endif // Y_ENVIRON_H
