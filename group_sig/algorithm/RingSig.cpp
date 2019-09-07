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

/* @file: RingSig.h
 * @author:fisco-bcos
 * @date:2019.09.05
 * @function: interface of group signature algorithm 
 */
#include <cryptopp/integer.h>
#include "group_sig/devcore/easylog.h"
#include "ring-sig/Common.h"
#include "ring-sig/LinkableRingSig_Impl.h"
#include "RingSig.h"
#include "group_sig/devcore/Base64.h"
#include "group_sig/devcore/StatusCode.h"

#if !defined(__cplusplus)
extern "C"
{
#endif

#if defined(__cplusplus)
        namespace RingSigApi
        {
        namespace LinkableRingSig
        {
#endif
        int setup_ring(std::string &param_info,
                       const int &bit_len)
        {
                LOG(DEBUG) << "setup ring...";
                CryptoPP::Integer p;
                std::string param;
                int ret = dev::eth::LinkableRingSigImpl::setup_ring(param, bit_len);
                if (ret == RetCode::CommonStatusCode::SUCCESS)
                {
                        param_info = dev::ToBase64(param);
                }
                return ret;
        }

        std::string setup_ring(const int &bit_len)
        {
                CryptoPP::Integer p;
                std::string param;
                if (dev::eth::LinkableRingSigImpl::setup_ring(param, bit_len))
                {
                        throw std::string("ring setup failed");
                }
                return dev::ToBase64(param);
        }

        int join_ring(std::string &private_key_info,
                      std::string &public_key_info,
                      const std::string &param_info,
                      const std::string &pos)
        {
                LOG(DEBUG) << "join ring...";
                std::string param;
                try
                {
                        param = dev::FromBase64(param_info);
                }
                catch (std::string &errorMsg)
                {
                        LOG(DEBUG) << errorMsg;
                        return RetCode::CommonStatusCode::DECODE_BASE64_ERR;
                }

                std::string private_key, public_key;
                int ret = dev::eth::LinkableRingSigImpl::join_ring(private_key,
                                                                   public_key, param, pos);
                if (ret == RetCode::CommonStatusCode::SUCCESS)
                {
                        private_key_info = dev::ToBase64(private_key);
                        public_key_info = dev::ToBase64(public_key);
                }
                return ret;
        }

        std::pair<std::string, std::string> join_ring(const std::string &param_info,
                                                      const std::string &pos)
        {
                std::string param;
                try
                {
                        param = dev::FromBase64(param_info);
                }
                catch (std::string &errorMsg)
                {
                        throw errorMsg;
                }
                std::string private_key, public_key;
                if (dev::eth::LinkableRingSigImpl::join_ring(private_key, public_key, param, pos))
                {
                        throw std::string("join ring failed");
                }
                std::pair<std::string, std::string> keypair;
                keypair.first = dev::ToBase64(private_key);
                keypair.second = dev::ToBase64(public_key);
                return keypair;
        }

        int ring_sig(std::string &sig,
                     const std::string &message,
                     const std::vector<std::string> &public_key_list,
                     const std::string &private_key_info,
                     const std::string &param_info)
        {
                LOG(DEBUG) << "generate sig...";
                std::string param, private_key;
                size_t size = public_key_list.size();
                std::vector<std::string> public_keys(size);
                try
                {
                        private_key = dev::FromBase64(private_key_info);
                        param = dev::FromBase64(param_info);
                        for (size_t i = 0; i < size; i++)
                        {
                                public_keys[i] = dev::FromBase64(public_key_list[i]);
                        }
                }
                catch (std::string &errorMsg)
                {
                        LOG(DEBUG) << errorMsg;
                        return RetCode::CommonStatusCode::DECODE_BASE64_ERR;
                }
                std::string sig_info;
                int ret = dev::eth::LinkableRingSigImpl::linkable_ring_sig(sig_info, message,
                                                                           public_keys, private_key, param);
                if (ret == RetCode::CommonStatusCode::SUCCESS)
                {
                        sig = dev::ToBase64(sig_info);
                }
                return ret;
        }

        std::string ring_sig(const std::string &message,
                             const std::vector<std::string> &public_key_list,
                             const std::string &private_key_info,
                             const std::string &param_info)
        {
                std::string param, private_key;
                size_t size = public_key_list.size();
                std::vector<std::string> public_keys(size);
                try
                {
                        private_key = dev::FromBase64(private_key_info);
                        param = dev::FromBase64(param_info);
                        for (size_t i = 0; i < size; i++)
                        {
                                public_keys[i] = dev::FromBase64(public_key_list[i]);
                        }
                }
                catch (std::string &errorMsg)
                {
                        throw errorMsg;
                }
                std::string sig_info;
                if (dev::eth::LinkableRingSigImpl::linkable_ring_sig(sig_info, message, public_keys, private_key, param))
                {
                        throw std::string("ring sig failed");
                }
                return dev::ToBase64(sig_info);
        }

        int ring_verify(bool &valid,
                        const std::string &sig,
                        const std::string &message,
                        const std::string &param_info)
        {
                LOG(DEBUG) << "ring sig verify...";
                std::string signature, param;
                try
                {
                        signature = dev::FromBase64(sig);
                        param = dev::FromBase64(param_info);
                }
                catch (std::string &errorMsg)
                {
                        LOG(DEBUG) << errorMsg;
                        return RetCode::CommonStatusCode::DECODE_BASE64_ERR;
                }
                return dev::eth::LinkableRingSigImpl::linkable_ring_verify(valid, signature, message, param);
        }

        bool ring_verify(const std::string &sig,
                         const std::string &message,
                         const std::string &param_info)
        {
                std::string signature, param;
                try
                {
                        signature = dev::FromBase64(sig);
                        param = dev::FromBase64(param_info);
                }
                catch (std::string &errorMsg)
                {
                        throw errorMsg;
                }
                bool valid;
                if (dev::eth::LinkableRingSigImpl::linkable_ring_verify(valid, signature, message, param))
                {
                        throw std::string("invalid inputs for verifing");
                }
                return valid;
        }

#if defined(__cplusplus)
        }
        }
#endif
#if !defined(__cplusplus)
}
#endif
