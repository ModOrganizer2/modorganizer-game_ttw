#include "gamefalloutttw.h"

#include "falloutttwbsainvalidation.h"
#include "falloutttwdataarchives.h"
#include "falloutttwscriptextender.h"
#include "falloutttwmoddatachecker.h"
#include "falloutttwmoddatacontent.h"
#include "falloutttwsavegame.h"

#include "executableinfo.h"
#include "pluginsetting.h"
#include "versioninfo.h"
#include <gamebryolocalsavegames.h>
#include <gamebryogameplugins.h>
#include <gamebryosavegameinfo.h>
#include <gamebryounmanagedmods.h>

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

#include <memory>

using namespace MOBase;

GameFalloutTTW::GameFalloutTTW()
{
}

void GameFalloutTTW::detectGame()
{
  GameGamebryo::detectGame();
  m_MyGamesPath = determineMyGamesPath("FalloutNV");
}

bool GameFalloutTTW::init(IOrganizer *moInfo)
{
  if (!GameGamebryo::init(moInfo)) {
    return false;
  }

  registerFeature<ScriptExtender>(new FalloutTTWScriptExtender(this));
  registerFeature<DataArchives>(new FalloutTTWDataArchives(myGamesPath()));
  registerFeature<BSAInvalidation>(new FalloutTTWBSAInvalidation(feature<DataArchives>(), this));
  registerFeature<SaveGameInfo>(new GamebryoSaveGameInfo(this));
  registerFeature<LocalSavegames>(new GamebryoLocalSavegames(myGamesPath(), "fallout.ini"));
  registerFeature<ModDataChecker>(new FalloutTTWModDataChecker(this));
  registerFeature<ModDataContent>(new FalloutTTWModDataContent(this));
  registerFeature<GamePlugins>(new GamebryoGamePlugins(moInfo));
  registerFeature<UnmanagedMods>(new GamebryoUnmangedMods(this));
  return true;
}

QString GameFalloutTTW::gameName() const
{
  return "TTW";
}

QList<ExecutableInfo> GameFalloutTTW::executables() const
{
  return QList<ExecutableInfo>()
      << ExecutableInfo("NVSE", findInGameFolder(feature<ScriptExtender>()->loaderName()))
      << ExecutableInfo("Tale of Two Wastelands", findInGameFolder(binaryName()))
      << ExecutableInfo("Fallout Launcher", findInGameFolder(getLauncherName()))
      << ExecutableInfo("Construction Kit", findInGameFolder("geck.exe"));
}

QList<ExecutableForcedLoadSetting> GameFalloutTTW::executableForcedLoads() const
{
  return QList<ExecutableForcedLoadSetting>();
}

QString GameFalloutTTW::name() const
{
  return "Fallout TTW Support Plugin";
}

QString GameFalloutTTW::localizedName() const
{
  return tr("Fallout TTW Support Plugin");
}

QString GameFalloutTTW::author() const
{
  return "SuperSandro2000";
}

QString GameFalloutTTW::description() const
{
  return tr("Adds support for the game Fallout TTW");
}

MOBase::VersionInfo GameFalloutTTW::version() const
{
  return VersionInfo(1, 5, 0, VersionInfo::RELEASE_FINAL);
}

QList<PluginSetting> GameFalloutTTW::settings() const
{
  return QList<PluginSetting>();
}

void GameFalloutTTW::initializeProfile(const QDir &path, ProfileSettings settings) const
{
  if (settings.testFlag(IPluginGame::MODS)) {
    copyToProfile(localAppFolder() + "/FalloutNV", path, "plugins.txt");
  }

  if (settings.testFlag(IPluginGame::CONFIGURATION)) {
    if (settings.testFlag(IPluginGame::PREFER_DEFAULTS)
        || !QFileInfo(myGamesPath() + "/fallout.ini").exists()) {
      copyToProfile(gameDirectory().absolutePath(), path, "fallout_default.ini", "fallout.ini");
    } else {
      copyToProfile(myGamesPath(), path, "fallout.ini");
    }

    copyToProfile(myGamesPath(), path, "falloutprefs.ini");
    copyToProfile(myGamesPath(), path, "falloutcustom.ini");
    copyToProfile(myGamesPath(), path, "GECKCustom.ini");
    copyToProfile(myGamesPath(), path, "GECKPrefs.ini");
  }
}

QString GameFalloutTTW::savegameExtension() const
{
  return "fos";
}

QString GameFalloutTTW::savegameSEExtension() const
{
  return "nvse";
}

std::shared_ptr<const GamebryoSaveGame> GameFalloutTTW::makeSaveGame(QString filePath) const
{
  return std::make_shared<const FalloutTTWSaveGame>(filePath, this);
}


QString GameFalloutTTW::steamAPPId() const
{
  return "22380";
}

QStringList GameFalloutTTW::primaryPlugins() const
{
  return { "falloutnv.esm",
           "deadmoney.esm",
           "honesthearts.esm",
           "oldworldblues.esm",
           "lonesomeroad.esm",
           "gunrunnersarsenal.esm",
           "fallout3.esm",
           "anchorage.esm",
           "thepitt.esm",
           "brokensteel.esm",
           "pointlookout.esm",
           "zeta.esm",
           "caravanpack.esm",
           "classicpack.esm",
           "mercenarypack.esm",
           "tribalpack.esm",
           "taleoftwowastelands.esm"
           "yupttw.esm" };
}

QString GameFalloutTTW::binaryName() const
{
  return "FalloutNV.exe";
}

QString GameFalloutTTW::gameShortName() const
{
  return "TTW";
}

QStringList GameFalloutTTW::primarySources() const
{
  return { "FalloutNV" };
}

QStringList GameFalloutTTW::validShortNames() const
{
  return { "FalloutNV", "Fallout3" };
}

QString GameFalloutTTW::gameNexusName() const
{
  return QString();
}

QStringList GameFalloutTTW::iniFiles() const
{
  return { "fallout.ini", "falloutprefs.ini", "falloutcustom.ini", "GECKCustom.ini", "GECKPrefs.ini" };
}

QStringList GameFalloutTTW::DLCPlugins() const
{
  return {};
}

MOBase::IPluginGame::SortMechanism GameFalloutTTW::sortMechanism() const
{
  return SortMechanism::NONE;
}

int GameFalloutTTW::nexusModOrganizerID() const
{
  return 0;
}

int GameFalloutTTW::nexusGameID() const
{
  return 0;
}

QString GameFalloutTTW::getLauncherName() const
{
  return "FalloutNVLauncher.exe";
}

QString GameFalloutTTW::identifyGamePath() const
{
  QString path = "Software\\Bethesda Softworks\\FalloutNV";
  return findInRegistry(HKEY_LOCAL_MACHINE, path.toStdWString().c_str(), L"Installed Path");
}

MappingType GameFalloutTTW::mappings() const
{
  MappingType result;

  for (const QString &profileFile : { "plugins.txt", "loadorder.txt" }) {
    result.push_back({ m_Organizer->profilePath() + "/" + profileFile,
      localAppFolder() + "/FalloutNV/" + profileFile,
      false });
  }

  return result;
}
