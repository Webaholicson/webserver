wsvt, config = {}, {}

function wscl (cmd)
  return_val = "";
  
  load (cmd)()
  
  return return_val
end

function config.site (fields)
  --[[ 
    Function for declaring a site.
    Simply returns the sites so the server
    can use it with the Lua C API
  ]]
  
  fields["type"] = "site"
  return_val = fields
end

function config.max_requests (value)
  wsvt["max_requests"] = value
end

function config.default_config_path (value)
  wsvt["default_config_path"] = value
end