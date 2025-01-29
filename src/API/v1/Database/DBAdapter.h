#pragma once

#include <vector>
#include <string>
#include "HTTP.h"

namespace v1 {

/**
 * @brief A template interface to interact with a certain database. To implement an interface on a database, 
 * implement the following methods:
 * 
 * - `bool DBAdapter::create`: reads from a request's body and creates an object in the given resource. It must return true if the resource is 
 * created successfully, or false otherwise. 
 * 
 * - `std::vector<std::string> DBAdapter::query`: reads from a request's query and returns a collections of data from the specified resource. 
 * The data must be represented in JSON form.
 * 
 * - `bool DBAdapter::update`: reads from a request's body and searches for the instance in the given resources. If the searching yields one 
 * object, the updates will be done on said object and the method returns true; otherwise it'll return false.
 * 
 * - `bool DBAdapter::delete` reads from a request's query and deletes the matching instance(s). The method returns true if the deletion is 
 * successful, and false otherwise.
 */
class DBAdapter {
protected: 
    // POST
    virtual bool create(const HTTP::Request& request) = 0;
    
    // GET
    virtual std::vector< std::string > query(const HTTP::Request& request) = 0;

    // PUT
    virtual bool update(const HTTP::Request& request) = 0;

    // DELETE
    virtual bool erase(const HTTP::Request& request) = 0; 
};

}