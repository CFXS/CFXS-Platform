#pragma once

#include <CFXS/Base/Types.hpp>

namespace CFXS::CPU {

    template<auto INITIAL_SP, VoidFunction_t RESET, VoidFunction_t DEFAULT_HANDLER>
    struct VectorTable {
        size_t _SP                      = (size_t)INITIAL_SP;
        VoidFunction_t _Reset           = RESET;
        VoidFunction_t _NMI             = DEFAULT_HANDLER;
        VoidFunction_t _HardFault       = DEFAULT_HANDLER;
        VoidFunction_t _MemManage_Fault = DEFAULT_HANDLER;
        VoidFunction_t _BusFault        = DEFAULT_HANDLER;
        VoidFunction_t _UsageFault      = DEFAULT_HANDLER;
        VoidFunction_t __reserved0      = nullptr;
        VoidFunction_t __reserved1      = nullptr;
        VoidFunction_t __reserved2      = nullptr;
        VoidFunction_t __reserved3      = nullptr;
        VoidFunction_t _SVCall          = DEFAULT_HANDLER;
        VoidFunction_t _DebugMonitor    = DEFAULT_HANDLER;
        VoidFunction_t __reserved4      = nullptr;
        VoidFunction_t _PendSV          = DEFAULT_HANDLER;
        VoidFunction_t _SysTick         = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_16   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_17   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_18   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_19   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_20   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_21   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_22   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_23   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_24   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_25   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_26   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_27   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_28   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_29   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_30   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_31   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_32   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_33   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_34   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_35   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_36   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_37   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_38   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_39   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_40   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_41   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_42   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_43   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_44   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_45   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_46   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_47   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_48   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_49   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_50   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_51   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_52   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_53   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_54   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_55   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_56   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_57   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_58   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_59   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_60   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_61   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_62   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_63   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_64   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_65   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_66   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_67   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_68   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_69   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_70   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_71   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_72   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_73   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_74   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_75   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_76   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_77   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_78   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_79   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_80   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_81   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_82   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_83   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_84   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_85   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_86   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_87   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_88   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_89   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_90   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_91   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_92   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_93   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_94   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_95   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_96   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_97   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_98   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_99   = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_100  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_101  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_102  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_103  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_104  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_105  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_106  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_107  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_108  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_109  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_110  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_111  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_112  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_113  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_114  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_115  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_116  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_117  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_118  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_119  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_120  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_121  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_122  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_123  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_124  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_125  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_126  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_127  = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_128  = DEFAULT_HANDLER;
#ifdef CFXS_LONG_VECTOR_TABLE
        VoidFunction_t __interrupt_129 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_130 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_131 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_132 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_133 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_134 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_135 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_136 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_137 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_138 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_139 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_140 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_141 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_142 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_143 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_144 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_145 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_146 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_147 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_148 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_149 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_150 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_151 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_152 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_153 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_154 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_155 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_156 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_157 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_158 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_159 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_160 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_161 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_162 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_163 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_164 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_165 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_166 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_167 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_168 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_169 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_170 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_171 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_172 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_173 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_174 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_175 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_176 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_177 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_178 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_179 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_180 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_181 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_182 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_183 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_184 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_185 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_186 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_187 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_188 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_189 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_190 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_191 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_192 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_193 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_194 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_195 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_196 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_197 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_198 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_199 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_200 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_201 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_202 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_203 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_204 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_205 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_206 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_207 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_208 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_209 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_210 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_211 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_212 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_213 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_214 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_215 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_216 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_217 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_218 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_219 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_220 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_221 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_222 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_223 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_224 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_225 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_226 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_227 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_228 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_229 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_230 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_231 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_232 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_233 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_234 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_235 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_236 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_237 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_238 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_239 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_240 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_241 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_242 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_243 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_244 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_245 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_246 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_247 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_248 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_249 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_250 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_251 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_252 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_253 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_254 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_255 = DEFAULT_HANDLER;
        VoidFunction_t __interrupt_256 = DEFAULT_HANDLER;
#endif
    };

} // namespace CFXS::CPU