/*
 * Stellarium
 * Copyright (C) 2002 Fabien Chereau
 * Copyright (c) 2010 Bogdan Marinov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef _SOLARSYSTEM_HPP_
#define _SOLARSYSTEM_HPP_
//sun is already defined in Sun C/Solaris
#if defined(sun)
#undef sun
#endif

#include "StelObjectModule.hpp"
#include "StelTextureTypes.hpp"
#include "Planet.hpp"
#include "StelGui.hpp"

#include <QFont>

class Orbit;
class StelTranslator;
class StelObject;
class StelCore;
class StelProjector;
class QSettings;

typedef QSharedPointer<Planet> PlanetP;

//! @class SolarSystem
//! This StelObjectModule derivative is used to model SolarSystem bodies.
//! This includes the Major Planets, Minor Planets and Comets.
class SolarSystem : public StelObjectModule
{
	Q_OBJECT
	Q_PROPERTY(bool labelsDisplayed // This is a "forwarding property" which sets labeling into all planets.
		   READ getFlagLabels
		   WRITE setFlagLabels
		   NOTIFY labelsDisplayedChanged)
	Q_PROPERTY(bool flagOrbits // was bool orbitsDisplayed
		   READ getFlagOrbits
		   WRITE setFlagOrbits
		   NOTIFY flagOrbitsChanged)
	Q_PROPERTY(bool trailsDisplayed
		   READ getFlagTrails
		   WRITE setFlagTrails
		   NOTIFY trailsDisplayedChanged)
	Q_PROPERTY(bool flagHints // was bool hintsDisplayed. This is a "forwarding property" only, without own variable.
		   READ getFlagHints
		   WRITE setFlagHints
		   NOTIFY flagHintsChanged)
	Q_PROPERTY(bool flagPointer // was bool pointersDisplayed
		   READ getFlagPointer
		   WRITE setFlagPointer
		   NOTIFY flagPointerChanged)
	Q_PROPERTY(bool flagNativePlanetNames // was bool nativeNamesDisplayed
		   READ getFlagNativePlanetNames
		   WRITE setFlagNativePlanetNames
		   NOTIFY flagNativePlanetNamesChanged)
	Q_PROPERTY(bool flagTranslatedNames
		   READ getFlagTranslatedNames
		   WRITE setFlagTranslatedNames
		   NOTIFY flagTranslatedNamesChanged)

	//StelProperties
	Q_PROPERTY(bool planetsDisplayed
		   READ getFlagPlanets
		   WRITE setFlagPlanets
		   NOTIFY flagPlanetsDisplayedChanged
		   )
	Q_PROPERTY(bool flagIsolatedOrbits
		   READ getFlagIsolatedOrbits
		   WRITE setFlagIsolatedOrbits
		   NOTIFY flagIsolatedOrbitsChanged
		   )
	Q_PROPERTY(bool flagIsolatedTrails
		   READ getFlagIsolatedTrails
		   WRITE setFlagIsolatedTrails
		   NOTIFY flagIsolatedTrailsChanged
		   )
	Q_PROPERTY(bool flagLightTravelTime
		   READ getFlagLightTravelTime
		   WRITE setFlagLightTravelTime
		   NOTIFY flagLightTravelTimeChanged
		   )
	Q_PROPERTY(bool flagMoonScale
		   READ getFlagMoonScale
		   WRITE setFlagMoonScale
		   NOTIFY flagMoonScaleChanged
		   )
	Q_PROPERTY(double moonScale
		   READ getMoonScale
		   WRITE setMoonScale
		   NOTIFY moonScaleChanged
		   )
	Q_PROPERTY(double labelsAmount
		   READ getLabelsAmount
		   WRITE setLabelsAmount
		   NOTIFY labelsAmountChanged
		   )
	Q_PROPERTY(bool ephemerisMarkersDisplayed
		   READ getFlagEphemerisMarkers
		   WRITE setFlagEphemerisMarkers
		   NOTIFY ephemerisMarkersChanged
		   )
	Q_PROPERTY(bool ephemerisDatesDisplayed
		   READ getFlagEphemerisDates
		   WRITE setFlagEphemerisDates
		   NOTIFY ephemerisDatesChanged
		   )

	Q_PROPERTY(bool flagCustomGrsSettings
		   READ getFlagCustomGrsSettings
		   WRITE setFlagCustomGrsSettings
		   NOTIFY flagCustomGrsSettingsChanged
		   )
	Q_PROPERTY(int customGrsLongitude
		   READ getCustomGrsLongitude
		   WRITE setCustomGrsLongitude
		   NOTIFY customGrsLongitudeChanged
		   )
	Q_PROPERTY(double customGrsDrift
		   READ getCustomGrsDrift
		   WRITE setCustomGrsDrift
		   NOTIFY customGrsDriftChanged
		   )
	Q_PROPERTY(double customGrsJD
		   READ getCustomGrsJD
		   WRITE setCustomGrsJD
		   NOTIFY customGrsJDChanged
		   )

	// Colors
	Q_PROPERTY(Vec3f orbitsColor
		   READ getOrbitsColor
		   WRITE setOrbitsColor
		   NOTIFY orbitsColorChanged
		   )
	Q_PROPERTY(Vec3f majorPlanetsOrbitsColor
		   READ getMajorPlanetsOrbitsColor
		   WRITE setMajorPlanetsOrbitsColor
		   NOTIFY majorPlanetsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f minorPlanetsOrbitsColor
		   READ getMinorPlanetsOrbitsColor
		   WRITE setMinorPlanetsOrbitsColor
		   NOTIFY minorPlanetsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f dwarfPlanetsOrbitsColor
		   READ getDwarfPlanetsOrbitsColor
		   WRITE setDwarfPlanetsOrbitsColor
		   NOTIFY dwarfPlanetsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f moonsOrbitsColor
		   READ getMoonsOrbitsColor
		   WRITE setMoonsOrbitsColor
		   NOTIFY moonsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f cubewanosOrbitsColor
		   READ getCubewanosOrbitsColor
		   WRITE setCubewanosOrbitsColor
		   NOTIFY cubewanosOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f plutinosOrbitsColor
		   READ getPlutinosOrbitsColor
		   WRITE setPlutinosOrbitsColor
		   NOTIFY plutinosOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f scatteredDiskObjectsOrbitsColor
		   READ getScatteredDiskObjectsOrbitsColor
		   WRITE setScatteredDiskObjectsOrbitsColor
		   NOTIFY scatteredDiskObjectsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f oortCloudObjectsOrbitsColor
		   READ getOortCloudObjectsOrbitsColor
		   WRITE setOortCloudObjectsOrbitsColor
		   NOTIFY oortCloudObjectsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f cometsOrbitsColor
		   READ getCometsOrbitsColor
		   WRITE setCometsOrbitsColor
		   NOTIFY cometsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f sednoidsOrbitsColor
		   READ getSednoidsOrbitsColor
		   WRITE setSednoidsOrbitsColor
		   NOTIFY sednoidsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f mercuryOrbitColor
		   READ getMercuryOrbitColor
		   WRITE setMercuryOrbitColor
		   NOTIFY mercuryOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f venusOrbitColor
		   READ getVenusOrbitColor
		   WRITE setVenusOrbitColor
		   NOTIFY venusOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f earthOrbitColor
		   READ getEarthOrbitColor
		   WRITE setEarthOrbitColor
		   NOTIFY earthOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f marsOrbitColor
		   READ getMarsOrbitColor
		   WRITE setMarsOrbitColor
		   NOTIFY marsOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f jupiterOrbitColor
		   READ getJupiterOrbitColor
		   WRITE setJupiterOrbitColor
		   NOTIFY jupiterOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f saturnOrbitColor
		   READ getSaturnOrbitColor
		   WRITE setSaturnOrbitColor
		   NOTIFY saturnOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f uranusOrbitColor
		   READ getUranusOrbitColor
		   WRITE setUranusOrbitColor
		   NOTIFY uranusOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f neptuneOrbitColor
		   READ getNeptuneOrbitColor
		   WRITE setNeptuneOrbitColor
		   NOTIFY neptuneOrbitColorChanged
		   )

	// Color style
	Q_PROPERTY(QString orbitColorStyle
		   READ getOrbitColorStyle
		   WRITE setOrbitColorStyle
		   NOTIFY orbitColorStyleChanged
		   )

public:
	SolarSystem();
	virtual ~SolarSystem();

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class
	//! Initialize the SolarSystem.
	//! Includes:
	//! - loading planetary body orbital and model data from data/ssystem.ini
	//! - perform initial planet position calculation
	//! - set display options from application settings
	virtual void init();

	virtual void deinit();
	
	//! Draw SolarSystem objects (planets).
	//! @param core The StelCore object.
	//! @return The maximum squared distance in pixels that any SolarSystem object
	//! has travelled since the last update.
	virtual void draw(StelCore *core);

	//! Update time-varying components.
	//! This includes planet motion trails.
	virtual void update(double deltaTime);

	//! Used to determine what order to draw the various StelModules.
	virtual double getCallOrder(StelModuleActionName actionName) const;

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in StelObjectManager class
	//! Search for SolarSystem objects in some area around a point.
	//! @param v A vector representing a point in the sky.
	//! @param limitFov The radius of the circle around the point v which
	//! defines the size of the area to search.
	//! @param core the core object
	//! @return A STL vector of StelObjectP (pointers) containing all SolarSystem
	//! objects found in the specified area. This vector is not sorted by distance
	//! from v.
	virtual QList<StelObjectP> searchAround(const Vec3d& v, double limitFov, const StelCore* core) const;

	//! Search for a SolarSystem object based on the localised name.
	//! @param nameI18n the case in-sensistive translated planet name.
	//! @return a StelObjectP for the object if found, else NULL.
	virtual StelObjectP searchByNameI18n(const QString& nameI18n) const;

	//! Search for a SolarSystem object based on the English name.
	//! @param name the case in-sensistive English planet name.
	//! @return a StelObjectP for the object if found, else NULL.
	virtual StelObjectP searchByName(const QString& name) const;

	virtual QStringList listAllObjects(bool inEnglish) const;
	virtual QStringList listAllObjectsByType(const QString& objType, bool inEnglish) const;
	virtual QString getName() const { return "Solar System"; }

public slots:
	///////////////////////////////////////////////////////////////////////////
	// Method callable from script and GUI
	// Properties setters and getters
	//! Set flag which determines if planets are drawn or hidden.
	void setFlagPlanets(bool b);
	//! Get the current value of the flag which determines if planet are drawn or hidden.
	bool getFlagPlanets() const;

	//! Set flag which determines if planet trails are drawn or hidden.
	void setFlagTrails(bool b);
	//! Get the current value of the flag which determines if planet trails are drawn or hidden.
	bool getFlagTrails() const;

	//! Set flag which determines if planet hints are drawn or hidden along labels
	void setFlagHints(bool b);
	//! Get the current value of the flag which determines if planet hints are drawn or hidden along labels
	bool getFlagHints() const;

	//! Set flag which determines if planet labels are drawn or hidden.
	void setFlagLabels(bool b);
	//! Get the current value of the flag which determines if planet labels are drawn or hidden.
	bool getFlagLabels() const;

	//! Set the amount of planet labels. The real amount is also proportional with FOV.
	//! The limit is set in function of the planets magnitude
	//! @param a the amount between 0 and 10. 0 is no labels, 10 is maximum of labels
	void setLabelsAmount(double a) {if(a!=labelsAmount) {labelsAmount=a; emit labelsAmountChanged(a);}}
	//! Get the amount of planet labels. The real amount is also proportional with FOV.
	//! @return the amount between 0 and 10. 0 is no labels, 10 is maximum of labels
	double getLabelsAmount(void) const {return labelsAmount;}

	//! Set flag which determines if planet orbits are drawn or hidden.
	void setFlagOrbits(bool b);
	//! Get the current value of the flag which determines if planet orbits are drawn or hidden.
	bool getFlagOrbits() const {return flagOrbits;}

	//! Set flag which determines if the planet pointer (red cross) is drawn or hidden on a selected planet.
	void setFlagPointer(bool b) { if (b!=flagPointer) { flagPointer=b; emit flagPointerChanged(b); }}
	//! Get the current value of the flag which determines if planet pointers are drawn or hidden.
	bool getFlagPointer() const { return flagPointer;}

	//! Set flag which determines if the light travel time calculation is used or not.
	void setFlagLightTravelTime(bool b);
	//! Get the current value of the flag which determines if light travel time
	//! calculation is used or not.
	bool getFlagLightTravelTime(void) const {return flagLightTravelTime;}

	//! Set planet names font size.
	//! @return font size
	void setFontSize(float newFontSize);

	//! Set the color used to draw planet labels.
	//! @param c The color of the planet labels (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setLabelsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setLabelsColor(const Vec3f& c);
	//! Get the current color used to draw planet labels.
	//! @return current color
	const Vec3f& getLabelsColor(void) const;

	//! Set the color used to draw solar system object orbit lines.
	//! @param c The color of the solar system object orbit lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw solar system object orbit lines.
	//! @return current color
	Vec3f getOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of the major planets.
	//! @param c The color of orbits lines of the major planets (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMajorPlanetsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMajorPlanetsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of the major planets.
	//! @return current color
	Vec3f getMajorPlanetsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of moons of planets.
	//! @param c The color of orbits lines of moons of planets lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMoonsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMoonsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of moons of planets.
	//! @return current color
	Vec3f getMoonsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of the minor planets.
	//! @param c The color of orbits lines of the minor planets (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMinorPlanetsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMinorPlanetsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of the minor planets.
	//! @return current color
	Vec3f getMinorPlanetsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of the dwarf planets.
	//! @param c The color of orbits lines of the dwarf planets (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setDwarfPlanetsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setDwarfPlanetsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of the dwarf planets.
	//! @return current color
	Vec3f getDwarfPlanetsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of cubewanos.
	//! @param c The color of orbits lines of cubewanos (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setCubewanosOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setCubewanosOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of cubewanos.
	//! @return current color
	Vec3f getCubewanosOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of plutinos.
	//! @param c The color of orbits lines of plutinos (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setPlutinosOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setPlutinosOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of plutinos.
	//! @return current color
	Vec3f getPlutinosOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of scattered disk objects.
	//! @param c The color of orbits lines of scattered disk objects (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setScatteredDiskObjectsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setScatteredDiskObjectsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of scattered disk objects.
	//! @return current color
	Vec3f getScatteredDiskObjectsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of Oort cloud objects.
	//! @param c The color of orbits lines of Oort cloud objects (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setOortCloudObjectsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setOortCloudObjectsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of Oort cloud objects.
	//! @return current color
	Vec3f getOortCloudObjectsOrbitsColor(void) const;

	//! Set the color used to draw comet orbit lines.
	//! @param c The color of the comet orbit lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setCometsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setCometsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw comet orbit lines.
	//! @return current color
	Vec3f getCometsOrbitsColor(void) const;

	//! Set the color used to draw sednoid orbit lines.
	//! @param c The color of the sednoid orbit lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setSednoidsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setSednoidsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw sednoid orbit lines.
	//! @return current color
	Vec3f getSednoidsOrbitsColor(void) const;

	//! Set the color used to draw Mercury orbit line.
	//! @param c The color of Mercury orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMercuryOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMercuryOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Mercury orbit line.
	//! @return current color
	Vec3f getMercuryOrbitColor(void) const;

	//! Set the color used to draw Venus orbit line.
	//! @param c The color of Venus orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setVenusOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setVenusOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Venus orbit line.
	//! @return current color
	Vec3f getVenusOrbitColor(void) const;

	//! Set the color used to draw Earth orbit line.
	//! @param c The color of Earth orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setEarthOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setEarthOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Earth orbit line.
	//! @return current color
	Vec3f getEarthOrbitColor(void) const;

	//! Set the color used to draw Mars orbit line.
	//! @param c The color of Mars orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMarsOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMarsOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Mars orbit line.
	//! @return current color
	Vec3f getMarsOrbitColor(void) const;

	//! Set the color used to draw Jupiter orbit line.
	//! @param c The color of Jupiter orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setJupiterOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setJupiterOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Jupiter orbit line.
	//! @return current color
	Vec3f getJupiterOrbitColor(void) const;

	//! Set the color used to draw Saturn orbit line.
	//! @param c The color of Saturn orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setSaturnOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setSaturnOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Saturn orbit line.
	//! @return current color
	Vec3f getSaturnOrbitColor(void) const;

	//! Set the color used to draw Uranus orbit line.
	//! @param c The color of Uranus orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setUranusOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setUranusOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Uranus orbit line.
	//! @return current color
	Vec3f getUranusOrbitColor(void) const;

	//! Set the color used to draw Neptune orbit line.
	//! @param c The color of Neptune orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setNeptuneOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setNeptuneOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Neptune orbit line.
	//! @return current color
	Vec3f getNeptuneOrbitColor(void) const;

	//! Set the color used to draw planet trails lines.
	//! @param c The color of the planet trails lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setTrailsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setTrailsColor(const Vec3f& c) {trailColor=c;}
	//! Get the current color used to draw planet trails lines.
	//! @return current color
	Vec3f getTrailsColor() const {return trailColor;}

	//! Set the color used to draw planet pointers.
	//! @param c The color of the planet pointers
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setPointerColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setPointerColor(const Vec3f& c) {pointerColor=c;}
	//! Get the current color used to draw planet pointers.
	//! @return current color
	Vec3f getPointerColor() const {return pointerColor;}

	//! Set flag which determines if Earth's moon is scaled or not.
	void setFlagMoonScale(bool b);
	//! Get the current value of the flag which determines if Earth's moon is scaled or not.
	bool getFlagMoonScale(void) const {return flagMoonScale;}

	//! Set the display scaling factor for Earth's moon.
	void setMoonScale(double f);
	//! Get the display scaling factor for Earth's moon.
	double getMoonScale(void) const {return moonScale;}

	//! Translate names. (public so that SolarSystemEditor can call it).
	void updateI18n();

	//! Get the V magnitude for Solar system bodies from scripts
	//! @param planetName the case in-sensistive English planet name.
	//! @param withExtinction the flag for use extinction effect for magnitudes (default not use)
	//! @return a magnitude
	float getPlanetVMagnitude(QString planetName, bool withExtinction=false) const;

	//! Get type for Solar system bodies from scripts
	//! @param planetName the case in-sensistive English planet name.
	//! @return a type of planet (planet, moon, asteroid, comet, plutoid)
	QString getPlanetType(QString planetName) const;

	//! Get distance to Solar system bodies from scripts
	//! @param planetName the case in-sensistive English planet name.
	//! @return a distance (in AU)
	double getDistanceToPlanet(QString planetName) const;

	//! Get elongation for Solar system bodies from scripts
	//! @param planetName the case in-sensistive English planet name.
	//! @return a elongation (in radians)
	double getElongationForPlanet(QString planetName) const;

	//! Get phase angle for Solar system bodies from scripts
	//! @param planetName the case in-sensistive English planet name.
	//! @return a phase angle (in radians)
	double getPhaseAngleForPlanet(QString planetName) const;

	//! Get phase for Solar system bodies from scripts
	//! @param planetName the case in-sensistive English planet name.
	//! @return a phase
	float getPhaseForPlanet(QString planetName) const;

	//! Set the algorithm for computation of apparent magnitudes for planets in case observer on the Earth.
	//! Possible values:
	//! @li @c Planesas (algorithm provided by Pere Planesas (Observatorio Astronomico Nacional))
	//! @li @c Mueller (G. Mueller, based on visual observations 1877-91. [Expl.Suppl.1961])
	//! @li @c Harris (Astronomical Almanac 1984 and later. These give V (instrumental) magnitudes)
	//! Details:
	//! @li J. Meeus "Astronomical Algorithms" (2nd ed., with corrections as of August 10, 2009) p.283-286.
	//! @li O. Montenbruck, T. Pfleger "Astronomy on the Personal Computer" (4th ed.) p.143-145.
	//! @li Daniel L. Harris "Photometry and Colorimetry of Planets and Satellites" http://adsabs.harvard.edu/abs/1961plsa.book..272H
	//! Hint: Default option in config.ini: astro/apparent_magnitude_algorithm = Harris
	//! @param algorithm the case in-sensitive algorithm name
	//! @note: The structure of algorithms is almost identical, just the numbers are different! You should activate
	//! Mueller's algorithm for simulate the eye's impression. (Esp. Venus!)
	void setApparentMagnitudeAlgorithmOnEarth(QString algorithm);

	//! Get the algorithm used for computation of apparent magnitudes for planets in case  observer on the Earth
	//! @see setApparentMagnitudeAlgorithmOnEarth()
	QString getApparentMagnitudeAlgorithmOnEarth() const;

	//! Set flag which enable use native names for planets or not.
	void setFlagNativePlanetNames(bool b);
	//! Get the current value of the flag which enables showing native names for planets or not.
	bool getFlagNativePlanetNames(void) const;

	//! Set flag which enable use translated names for planets or not.
	void setFlagTranslatedNames(bool b);
	//! Get the current value of the flag which enables showing translated names for planets or not.
	bool getFlagTranslatedNames(void) const;

	//! Set flag which enabled the showing of isolated trails for selected objects only or not
	void setFlagIsolatedTrails(bool b);
	//! Get the current value of the flag which enables showing of isolated trails for selected objects only or not.
	bool getFlagIsolatedTrails(void) const;

	//! Set flag which enabled the showing of isolated orbits for selected objects only or not
	void setFlagIsolatedOrbits(bool b);
	//! Get the current value of the flag which enables showing of isolated orbits for selected objects only or not.
	bool getFlagIsolatedOrbits(void) const;

	//! Set flag which determines if custom settings is using for Great Red Spot on Jupiter
	void setFlagCustomGrsSettings(bool b);
	//! Get the current value of the flag which determines if custom settings for Great Red Spot on Jupiter is used or not.
	bool getFlagCustomGrsSettings();

	//! Set longitude of Great Red Spot (System II is used)
	//! @param longitude (degrees)
	void setCustomGrsLongitude(int longitude);
	//! Get longitude of Great Red Spot (System II is used)
	//! @return a longitude (degrees)
	int getCustomGrsLongitude();

	//! Set speed of annual drift for Great Red Spot (System II is used)
	//! @param annual drift (degrees)
	void setCustomGrsDrift(double drift);
	//! Get speed of annual drift for Great Red Spot (System II is used)
	double getCustomGrsDrift();

	//! Set initial JD for calculation of position of Great Red Spot
	//! @param JD
	// TODO (GZ): Clarify whether this is JD or rather JDE?
	void setCustomGrsJD(double JD);
	//! Get initial JD for calculation of position of Great Red Spot
	double getCustomGrsJD();

	//! Set style of colors of orbits for Solar system bodies
	void setOrbitColorStyle(QString style);
	//! Get style of colors of orbits for Solar system bodies
	QString getOrbitColorStyle() const;

	//! Get list of objects by type
	//! @param objType object type
	QStringList getObjectsList(QString objType="all") const;

signals:
	void labelsDisplayedChanged(bool b);
	void flagOrbitsChanged(bool b);
	void flagHintsChanged(bool b);
	void trailsDisplayedChanged(bool b);
	void flagPointerChanged(bool b);
	void flagNativePlanetNamesChanged(bool b);
	void flagTranslatedNamesChanged(bool b);
	void flagPlanetsDisplayedChanged(bool b);
	void flagIsolatedOrbitsChanged(bool b);
	void flagIsolatedTrailsChanged(bool b);
	void flagLightTravelTimeChanged(bool b);
	void flagMoonScaleChanged(bool b);
	void moonScaleChanged(double f);
	void labelsAmountChanged(double f);
	void ephemerisMarkersChanged(bool b);
	void ephemerisDatesChanged(bool b);
	void flagCustomGrsSettingsChanged(bool b);
	void customGrsLongitudeChanged(int l);
	void customGrsDriftChanged(double drift);
	void customGrsJDChanged(double JD);

	void orbitsColorChanged(const Vec3f & color) const;
	void majorPlanetsOrbitsColorChanged(const Vec3f & color) const;
	void minorPlanetsOrbitsColorChanged(const Vec3f & color) const;
	void dwarfPlanetsOrbitsColorChanged(const Vec3f & color) const;
	void moonsOrbitsColorChanged(const Vec3f & color) const;
	void cubewanosOrbitsColorChanged(const Vec3f & color) const;
	void plutinosOrbitsColorChanged(const Vec3f & color) const;
	void scatteredDiskObjectsOrbitsColorChanged(const Vec3f & color) const;
	void oortCloudObjectsOrbitsColorChanged(const Vec3f & color) const;
	void cometsOrbitsColorChanged(const Vec3f & color) const;
	void sednoidsOrbitsColorChanged(const Vec3f & color) const;
	void mercuryOrbitColorChanged(const Vec3f & color) const;
	void venusOrbitColorChanged(const Vec3f & color) const;
	void earthOrbitColorChanged(const Vec3f & color) const;
	void marsOrbitColorChanged(const Vec3f & color) const;
	void jupiterOrbitColorChanged(const Vec3f & color) const;
	void saturnOrbitColorChanged(const Vec3f & color) const;
	void uranusOrbitColorChanged(const Vec3f & color) const;
	void neptuneOrbitColorChanged(const Vec3f & color) const;

	void orbitColorStyleChanged(QString style) const;

	void solarSystemDataReloaded();

public:
	///////////////////////////////////////////////////////////////////////////
	// Other public methods
	//! Get a pointer to a Planet object.
	//! @param planetEnglishName the English name of the desired planet.
	//! @return The matching planet pointer if exists or NULL.
	PlanetP searchByEnglishName(QString planetEnglishName) const;

	//! Get the Planet object pointer for the Sun.
	PlanetP getSun() const {return sun;}

	//! Get the Planet object pointer for the Earth.
	PlanetP getEarth() const {return earth;}

	//! Get the Planet object pointer for Earth's moon.
	PlanetP getMoon() const {return moon;}

	//! Determine if a lunar eclipse is close at hand?
	bool nearLunarEclipse();

	//! Get the list of all the planet english names
	QStringList getAllPlanetEnglishNames() const;

	//! Get the list of all the planet localized names
	QStringList getAllPlanetLocalizedNames() const;

	//! Reload the planets
	void reloadPlanets();

	//! Determines relative amount of sun visible from the observer's position.
	double getEclipseFactor(const StelCore *core) const;

	//! Compute the position and transform matrix for every element of the solar system.
	//! @param observerPos Position of the observer in heliocentric ecliptic frame (Required for light travel time computation).
	//! @param dateJDE the Julian Day in JDE (Ephemeris Time or equivalent)	
	void computePositions(double dateJDE, const Vec3d& observerPos = Vec3d(0.));

	//! Get the list of all the bodies of the solar system.	
	const QList<PlanetP>& getAllPlanets() const {return systemPlanets;}	

private slots:
	//! Called when a new object is selected.
	void selectedObjectChange(StelModule::StelModuleSelectAction action);

	//! Called when the sky culture is updated.
	//! Loads native names of planets for a given sky culture.
	//! @param skyCultureDir the name of the directory containing the sky culture to use.
	void updateSkyCulture(const QString& skyCultureDir);

	void setFlagEphemerisMarkers(bool b);
	bool getFlagEphemerisMarkers() const;

	void setFlagEphemerisDates(bool b);
	bool getFlagEphemerisDates() const;

private:
	//! Search for SolarSystem objects which are close to the position given
	//! in earth equatorial position.
	//! @param v A position in earth equatorial position.
	//! @param core the StelCore object.
	//! @return a pointer to a StelObject if found, else NULL
	StelObjectP search(Vec3d v, const StelCore* core) const;

	//! Compute the transformation matrix for every elements of the solar system.
	//! observerPos is needed for light travel time computation.
	void computeTransMatrices(double dateJDE, const Vec3d& observerPos = Vec3d(0.));

	//! Draw a nice animated pointer around the object.
	void drawPointer(const StelCore* core);

	//! Load planet data from the Solar System configuration file.
	//! This function attempts to load every possible instance of the
	//! Solar System configuration file in the file paths, falling back if a
	//! given path can't be loaded.
	void loadPlanets();

	//! Load planet data from the given file
	bool loadPlanets(const QString& filePath);

	void recreateTrails();

	//! Set flag who enable display a permanent orbits for objects or not
	void setFlagPermanentOrbits(bool b);

	//! Used to count how many planets actually need shadow information
	int shadowPlanetCount;
	PlanetP sun;
	PlanetP moon;
	PlanetP earth;

	//! Set selected planets by englishName.
	//! @param englishName The planet name or "" to select no planet
	void setSelected(const QString& englishName);
	//! Set selected object from its pointer.
	void setSelected(PlanetP obj);
	//! Get selected object's pointer.
	PlanetP getSelected(void) const {return selected;}
	//! The currently selected planet.
	PlanetP selected;

	// Moon scale value
	bool flagMoonScale;
	double moonScale;

	QFont planetNameFont;

	//! The amount of planets labels (between 0 and 10).
	double labelsAmount;

	//! List of all the bodies of the solar system.
	QList<PlanetP> systemPlanets;

	// Master settings
	bool flagOrbits;
	bool flagLightTravelTime;

	//! The selection pointer texture.
	StelTextureSP texPointer;
	StelTextureSP texCircle;                    // The symbolic circle texture

	bool flagShow;
	bool flagPointer;                           // show red cross selection pointer?
	bool flagNativePlanetNames;                 // show native names for planets?
	bool flagTranslatedNames;                   // show translated names?
	bool flagIsolatedTrails;
	bool flagIsolatedOrbits;
	bool ephemerisMarkersDisplayed;
	bool ephemerisDatesDisplayed;

	class TrailGroup* allTrails;
	StelGui* gui;
	QSettings* conf;
	LinearFader trailFader;
	Vec3f trailColor;
	Vec3f pointerColor;

	QHash<QString, QString> planetNativeNamesMap;

	QList<Orbit*> orbits;           // Pointers on created elliptical orbits
};


#endif // _SOLARSYSTEM_HPP_
