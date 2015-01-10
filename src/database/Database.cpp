#include "Database.h"

#include "Logger.h"

#include "mongo/bson/bson.h"
#include "mongo/db/json.h"

#include <fstream>
#include <sstream>

Database::Database() {
    mongo::client::initialize();
    std::fstream file("internal.json", std::fstream::in | std::fstream::out);
    std::stringstream buffer;
    buffer << file.rdbuf();
    mongo::BSONObj internal = mongo::fromjson(buffer.str());
    if (internal.hasElement("_id"))
        _id = internal["_id"].OID();
    else
        _id.init();
    mongo::BSONObjBuilder internalObj;
    internalObj.append("_id", _id);
    internalObj.appendElementsUnique(internal);
    file.seekg(0);
    file << internalObj.obj().jsonString();
    file.close();
}

bool Database::run() {
    try {
        c.connect("localhost");
        Logger() << "Connexion à MongoDB établie avec succès" << std::endl;
        return true;
    } catch (const mongo::DBException &e) {
        Logger(LogLevel::WARNING) << "IMPOSSIBLE DE SE CONNECTER À MONGODB !" << std::endl;
        Logger(LogLevel::WARNING) << "L'erreur rencontrée est : " << e.what() << std::endl;
        Logger(LogLevel::WARNING) << "Peut-être que MongoDB n'est pas lancé ?" << std::endl;
    }
    return false;
}

Profile *Database::getProfile(string_t name) {
    auto cursor = c.query("mf.profiles", BSON("name" << name));
    if (cursor->more()) {
        Profile *profile = new Profile(name);
        mongo::BSONObj profileObj = cursor->next();
        profile->uuid = profileObj["_id"].String();
        profile->name = profileObj["name"].String();
        profile->properties.clear();
        std::vector<mongo::BSONElement> properties = profileObj["properties"].Array();
        for (auto it = properties.begin(); it != properties.end(); ++it) {
            Profile::Property property;
            mongo::BSONObj propertyObj = (*it).Obj();
            property.name = propertyObj["name"].String();
            property.value = propertyObj["value"].String();
            property.isSigned = propertyObj["isSigned"].Bool();
            if (property.isSigned)
                property.signature = propertyObj["signature"].String();
            profile->properties.push_back(property);
        }
        return profile;
    }
    return nullptr;
}

void Database::addServer(ushort_t port) {
    c.update("mf.servers", BSON("_id" << _id), BSON("$set" << BSON("host" << "0.0.0.0" << "port" << port)), true);
}

void Database::removeServer() {
    c.remove("mf.servers", BSON("_id" << _id));
}
