#include "Database.h"

#include "Logger.h"

#include "mongo/bson/bson.h"

Database::Database() {
    mongo::client::initialize();
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
