/*
	This file is part of FISCO BCOS.

	FISCO BCOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FISCO BCOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FISCO BCOS.  If not, see <http://www.gnu.org/licenses/>.
*/

/* @file: GroupSig.cpp
 * @author:fisco-bcos
 * @date:2018.03.07
 * @function: interface implementation of group signature algorithm 
 */

#include <time.h>
#include "GroupSigFactory.h"
#include "group_sig/devcore/easylog.h"
#include "group_sig/devcore/CommonFunc.h"
#include "GroupSig.h"
#include "group_sig/devcore/StatusCode.h"
#include "group_sig/devcore/Base64.h"

using namespace dev;
using namespace dev::eth;
using namespace RetCode::CommonStatusCode;

GroupSigMethod SIG_METHOD = BBS04;

#if defined(__cplusplus)
namespace GroupSigApi
{
#endif

inline vector<string> string_split(const std::string &str, const string &delim)
{
        char *outer = NULL;
        char *result = strtok_r((char *)str.c_str(), delim.c_str(), &outer);
        vector<string> result_vec;
        while (result)
        {
                result_vec.push_back(std::string(result));
                result = strtok_r(NULL, delim.c_str(), &outer);
        }
        return result_vec;
}

int create_group_default(std::string &result,
                         const std::string &algorithm_method)
{
        LOG(DEBUG) << "CREATE GROUP WITH DEFAULT PARAM";
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string param = "";
        return GroupSigFactory::instance(method)->create_group(result, param);
}

GroupInfo create_group_default()
{
        std::string temp;
        std::string param = "";
        if (GroupSigFactory::instance(SIG_METHOD)->create_group(temp, param))
        {
                throw std::string("create group failed");
        }
        vector<string> vs = string_split(temp, BBSGroupSig::RET_DELIM);
        GroupInfo result(vs[0], vs[1], vs[2], vs[3]);
        return result;
}

int create_group(std::string &result,
                 const std::string &algorithm_method,
                 const std::string &pbc_param_info)
{
        LOG(DEBUG) << "CREATE GROUP WITH SPECIFIED PARAM:" << pbc_param_info;
        LOG(DEBUG) << "METHOD = " << algorithm_method;
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string param;
        try
        {
                param = FromBase64(pbc_param_info);
        }
        catch (std::string &errorMsg)
        {
                LOG(DEBUG) << errorMsg;
                return DECODE_BASE64_ERR;
        }
        return GroupSigFactory::instance(method)->create_group(result, param);
}

GroupInfo create_group(const std::string &pbc_param_str)
{
        std::string param;
        try
        {
                param = FromBase64(pbc_param_str);
        }
        catch (std::string &errorMsg)
        {
                throw errorMsg;
        }
        std::string temp;
        if (GroupSigFactory::instance(SIG_METHOD)->create_group(temp, param))
        {
                throw std::string("create group failed");
        }
        vector<string> vs = string_split(temp, BBSGroupSig::RET_DELIM);
        GroupInfo result(vs[0], vs[1], vs[2], vs[3]);
        return result;
}

//group  member join: group manager generate private key && cert for group members
int group_member_join(std::string &sk,
                      const std::string &algorithm_method,
                      const std::string &pbc_param_info,
                      const std::string &gmsk_info,
                      const std::string &gpk_info,
                      const std::string &gamma_info)
{
        LOG(DEBUG) << "GROUP MEMBER JOIN";
        LOG(DEBUG) << "METHOD = " << algorithm_method;
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string param, gmsk, gpk, gamma;
        try
        {
                param = FromBase64(pbc_param_info);
                gmsk = FromBase64(gmsk_info);
                gpk = FromBase64(gpk_info);
                gamma = FromBase64(gamma_info);
        }
        catch (std::string &errorMsg)
        {
                LOG(DEBUG) << errorMsg;
                return DECODE_BASE64_ERR;
        }

        std::string params = param + _get_split_symbol();
        params += gmsk + _get_split_symbol();
        params += gpk + _get_split_symbol();
        params += gamma;
        LOG(DEBUG) << "PARAMS IS:" << params;
        std::string sk_info;
        int ret = GroupSigFactory::instance(method)->gen_gsk(sk_info, params);
        if (ret == SUCCESS)
        {
                sk = ToBase64(sk_info);
        }
        return ret;
}

std::string group_member_join(const std::string &pbc_param_info,
                              const std::string &gmsk_info,
                              const std::string &gpk_info,
                              const std::string &gamma_info)
{
        std::string param, gmsk, gpk, gamma;
        try
        {
                param = FromBase64(pbc_param_info);
                gmsk = FromBase64(gmsk_info);
                gpk = FromBase64(gpk_info);
                gamma = FromBase64(gamma_info);
        }
        catch (std::string &errorMsg)
        {
                throw errorMsg;
        }
        std::string params = param + _get_split_symbol();
        params += gmsk + _get_split_symbol();
        params += gpk + _get_split_symbol();
        params += gamma;
        std::string sk_info;
        if (GroupSigFactory::instance(SIG_METHOD)->gen_gsk(sk_info, params))
        {
                throw std::string("join group failed");
        }
        return ToBase64(sk_info);
}

//implementation of group sig
int group_sig(std::string &sig,
              const std::string &algorithm_method,
              const std::string &gpk_info,
              const std::string &sk_info,
              const std::string &pbc_param_info,
              const std::string &message)
{
        LOG(DEBUG) << "GROUP SIG";
        LOG(DEBUG) << "METHOD = " << algorithm_method;
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string gpk, sk, param;
        try
        {
                gpk = FromBase64(gpk_info);
                sk = FromBase64(sk_info);
                param = FromBase64(pbc_param_info);
        }
        catch (std::string &errorMsg)
        {
                LOG(DEBUG) << errorMsg;
                return DECODE_BASE64_ERR;
        }
        std::string params = gpk + _get_split_symbol();
        params += sk + _get_split_symbol();
        params += param + _get_split_symbol();
        params += message;
        LOG(DEBUG) << "PARAMS is:" << params;
        std::string signature;
        int ret = GroupSigFactory::instance(method)->group_sig(signature, params);
        if (ret == SUCCESS)
        {
                sig = ToBase64(signature);
        }
        return ret;
}

std::string group_sig(const std::string &gpk_info,
                      const std::string &sk_info,
                      const std::string &pbc_param_info,
                      const std::string &message)
{
        std::string gpk, sk, param;
        try
        {
                gpk = FromBase64(gpk_info);
                sk = FromBase64(sk_info);
                param = FromBase64(pbc_param_info);
        }
        catch (std::string &errorMsg)
        {
                throw errorMsg;
        }
        std::string params = gpk + _get_split_symbol();
        params += sk + _get_split_symbol();
        params += param + _get_split_symbol();
        params += message;
        std::string signature;
        if (GroupSigFactory::instance(SIG_METHOD)->group_sig(signature, params))
        {
                throw std::string("group sig failed");
        }
        return ToBase64(signature);
}

//implementation of group verify
int group_verify(int &valid,
                 const std::string &sig,
                 const std::string &message,
                 const std::string &algorithm_method,
                 const std::string &gpk_info,
                 const std::string &pbc_param_info)
{
        LOG(DEBUG) << "BBS04 GROUP VERFIFY";
        LOG(DEBUG) << "METHOD = " << algorithm_method;
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string signature, gpk, param;
        try
        {
                signature = FromBase64(sig);
                gpk = FromBase64(gpk_info);
                param = FromBase64(pbc_param_info);
        }
        catch (std::string &errorMsg)
        {
                LOG(DEBUG) << errorMsg;
                return DECODE_BASE64_ERR;
        }
        std::string params = signature + _get_split_symbol();
        params += message + _get_split_symbol();
        params += gpk + _get_split_symbol();
        params += param;
        LOG(DEBUG) << "PARAMS:" << params;
        return GroupSigFactory::instance(method)->group_verify(valid, params);
}

bool group_verify(const std::string &sig,
                  const std::string &message,
                  const std::string &gpk_info,
                  const std::string &pbc_param_info)
{
        std::string signature, gpk, param;
        try
        {
                signature = FromBase64(sig);
                gpk = FromBase64(gpk_info);
                param = FromBase64(pbc_param_info);
        }
        catch (std::string &errorMsg)
        {
                throw errorMsg;
        }
        std::string params = signature + _get_split_symbol();
        params += message + _get_split_symbol();
        params += gpk + _get_split_symbol();
        params += param;
        int valid;
        if (GroupSigFactory::instance(SIG_METHOD)->group_verify(valid, params))
        {
                throw std::string("verify group signature failed");
        }
        if (valid)
        {
                return true;
        }
        else
        {
                return false;
        }
}

//implementation of group open with given signature
int open_cert(std::string &cert,
              const std::string &algorithm_method,
              const std::string &sig,
              const std::string &message,
              const std::string &gpk_info,
              const std::string &gmsk_info,
              const std::string &pbc_param_info)
{
        LOG(DEBUG) << "BBS04 OPEN CERT";
        LOG(DEBUG) << "METHOD = " << algorithm_method;
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string signature, gpk, gmsk, param;
        try
        {
                signature = FromBase64(sig);
                gpk = FromBase64(gpk_info);
                gmsk = FromBase64(gmsk_info);
                param = FromBase64(pbc_param_info);
        }
        catch (std::string &errorMsg)
        {
                LOG(DEBUG) << errorMsg;
                return DECODE_BASE64_ERR;
        }

        std::string params = signature + _get_split_symbol();
        params += message + _get_split_symbol();
        params += gpk + _get_split_symbol();
        params += gmsk + _get_split_symbol();
        params += param;
        LOG(DEBUG) << "PARAMS:" << params;
        std::string temp;
        int ret = GroupSigFactory::instance(method)->group_open(temp, params);
        if (ret == SUCCESS)
        {
                cert = ToBase64(temp);
        }
        return ret;
}
std::string open_cert(const std::string &sig,
                      const std::string &message,
                      const std::string &gpk_info,
                      const std::string &gmsk_info,
                      const std::string &pbc_param_info)
{
        std::string signature, gpk, gmsk, param;
        try
        {
                signature = FromBase64(sig);
                gpk = FromBase64(gpk_info);
                gmsk = FromBase64(gmsk_info);
                param = FromBase64(pbc_param_info);
        }
        catch (std::string &errorMsg)
        {
                throw errorMsg;
        }

        std::string params = signature + _get_split_symbol();
        params += message + _get_split_symbol();
        params += gpk + _get_split_symbol();
        params += gmsk + _get_split_symbol();
        params += param;
        std::string cert;
        if (GroupSigFactory::instance(SIG_METHOD)->group_open(cert, params))
        {
                throw std::string("open group signature failed");
        }
        return ToBase64(cert);
}

//update gpk when group memeber revoked
int revoke_member(std::string &gpk,
                  const std::string &algorithm_method,
                  const std::string &pbc_param,
                  const std::string &revoke_info,
                  const std::string &gamma_info)
{
        LOG(DEBUG) << "BBS04 REVOKE MEMBER";
        LOG(DEBUG) << "METHOD = " << algorithm_method;
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string param, revoke, gamma;
        try
        {
                param = FromBase64(pbc_param);
                revoke = FromBase64(revoke_info);
                gamma = FromBase64(gamma_info);
        }
        catch (std::string &errorMsg)
        {
                LOG(DEBUG) << errorMsg;
                return DECODE_BASE64_ERR;
        }
        std::string params = param + _get_split_symbol();
        params += revoke + _get_split_symbol();
        params += gamma;

        LOG(DEBUG) << "PARAMS:" << params;
        std::string temp;
        int ret = GroupSigFactory::instance(method)->gm_revoke(temp, params);
        if (ret == SUCCESS)
        {
                gpk = ToBase64(temp);
        }
        return ret;
}
std::string revoke_member(const std::string &pbc_param,
                          const std::string &revoke_info,
                          const std::string &gamma_info)
{
        std::string param, revoke, gamma;
        try
        {
                param = FromBase64(pbc_param);
                revoke = FromBase64(revoke_info);
                gamma = FromBase64(gamma_info);
        }
        catch (std::string &errorMsg)
        {
                throw errorMsg;
        }
        std::string params = param + _get_split_symbol();
        params += revoke + _get_split_symbol();
        params += gamma;
        std::string gpk;
        if (GroupSigFactory::instance(SIG_METHOD)->gm_revoke(gpk, params))
        {
                throw std::string("revoke member failed");
        }
        return ToBase64(gpk);
}

//update group member private key after some members revoked
int revoke_update_private_key(std::string &sk,
                              const std::string &algorithm_method,
                              const std::string &pbc_param,
                              const std::string &revoke_list,
                              const std::string &gone_list,
                              const std::string &gpk_info)
{
        LOG(DEBUG) << "UPDATE GSK AFTER REVOKE member";
        LOG(DEBUG) << "METHOD = " << algorithm_method;
        GroupSigMethod method = get_algo_method_by_string(algorithm_method);
        std::string param, revoke, gone, gpk;
        try
        {
                param = FromBase64(pbc_param);
                revoke = FromBase64(revoke_list);
                gone = FromBase64(gone_list);
                gpk = FromBase64(gpk_info);
        }
        catch (std::string &errorMsg)
        {
                LOG(DEBUG) << errorMsg;
                return DECODE_BASE64_ERR;
        }
        std::string params = param + _get_split_symbol();
        params += revoke + _get_split_symbol();
        params += gone + _get_split_symbol();
        params += gpk;
        LOG(DEBUG) << "PARAMS:" << params;
        std::string temp;
        int ret = GroupSigFactory::instance(method)->update_gsk(temp, params);
        if (ret == SUCCESS)
        {
                sk = ToBase64(temp);
        }
        return ret;
}
std::string revoke_update_private_key(const std::string &pbc_param,
                                      const std::string &revoke_list,
                                      const std::string &gone_list,
                                      const std::string &gpk_info)
{
        std::string param, revoke, gone, gpk;
        try
        {
                param = FromBase64(pbc_param);
                revoke = FromBase64(revoke_list);
                gone = FromBase64(gone_list);
                gpk = FromBase64(gpk_info);
        }
        catch (std::string &errorMsg)
        {
                throw errorMsg;
        }
        std::string params = param + _get_split_symbol();
        params += revoke + _get_split_symbol();
        params += gone + _get_split_symbol();
        params += gpk;
        LOG(DEBUG) << "PARAMS:" << params;
        std::string sk;
        if (GroupSigFactory::instance(SIG_METHOD)->update_gsk(sk, params))
        {
                throw std::string("rupdate group member private key failed");
        }
        return ToBase64(sk);
}

#if defined(__cplusplus)
}
#endif
