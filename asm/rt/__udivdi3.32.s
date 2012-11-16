;-------------------------------------------------------------------------------
; XEOS - X86 Experimental Operating System
; 
; Copyright (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
; All rights reserved.
; 
; XEOS Software License - Version 1.0 - December 21, 2012
; 
; Permission is hereby granted, free of charge, to any person or organisation
; obtaining a copy of the software and accompanying documentation covered by
; this license (the "Software") to deal in the Software, with or without
; modification, without restriction, including without limitation the rights
; to use, execute, display, copy, reproduce, transmit, publish, distribute,
; modify, merge, prepare derivative works of the Software, and to permit
; third-parties to whom the Software is furnished to do so, all subject to the
; following conditions:
; 
;       1.  Redistributions of source code, in whole or in part, must retain the
;           above copyright notice and this entire statement, including the
;           above license grant, this restriction and the following disclaimer.
; 
;       2.  Redistributions in binary form must reproduce the above copyright
;           notice and this entire statement, including the above license grant,
;           this restriction and the following disclaimer in the documentation
;           and/or other materials provided with the distribution, unless the
;           Software is distributed by the copyright owner as a library.
;           A "library" means a collection of software functions and/or data
;           prepared so as to be conveniently linked with application programs
;           (which use some of those functions and data) to form executables.
; 
;       3.  The Software, or any substancial portion of the Software shall not
;           be combined, included, derived, or linked (statically or
;           dynamically) with software or libraries licensed under the terms
;           of any GNU software license, including, but not limited to, the GNU
;           General Public License (GNU/GPL) or the GNU Lesser General Public
;           License (GNU/LGPL).
; 
;       4.  All advertising materials mentioning features or use of this
;           software must display an acknowledgement stating that the product
;           includes software developed by the copyright owner.
; 
;       5.  Neither the name of the copyright owner nor the names of its
;           contributors may be used to endorse or promote products derived from
;           this software without specific prior written permission.
; 
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER AND CONTRIBUTORS "AS IS"
; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
; THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
; PURPOSE, TITLE AND NON-INFRINGEMENT ARE DISCLAIMED.
; 
; IN NO EVENT SHALL THE COPYRIGHT OWNER, CONTRIBUTORS OR ANYONE DISTRIBUTING
; THE SOFTWARE BE LIABLE FOR ANY CLAIM, DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
; EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
; WHETHER IN ACTION OF CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
; NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF OR IN CONNECTION WITH
; THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE, EVEN IF ADVISED
; OF THE POSSIBILITY OF SUCH DAMAGE.
;-------------------------------------------------------------------------------

; $Id$

;-------------------------------------------------------------------------------
; @file            __udivdi3.32.s
; @author          Jean-David Gadina
; @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; ABOUT / COPYRIGHT NOTICE
;-------------------------------------------------------------------------------
; 
; 
; 
;-------------------------------------------------------------------------------
; ORIGINAL LICENSE
;-------------------------------------------------------------------------------
; 
; Copyright (c) 2008 Stephen Canon
; 
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
; 
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
; THE SOFTWARE.
;-------------------------------------------------------------------------------

global __udivdi3

;-------------------------------------------------------------------------------
; du_int __udivdi3( du_int a, du_int b );
; 
; result = a / b
; 
; Both inputs and the output are 64-bit unsigned integers.
; This will do whatever the underlying hardware is set to do on division by
; zero.
; No other exceptions are generated, as the divide cannot overflow.
;
; This is targeted at 32-bit x86 *only*, as this can be done directly in
; hardware on x86_64.
; The performance goal is ~40 cycles per divide, which is faster than
; currently possible via simulation of integer divides on the x87 unit.
;-------------------------------------------------------------------------------
__udivdi3:
    
    push    ebx
    
    ; Find the index i of the leading bit in b
    mov     ebx,        [ esp + 20 ]
    bsr     ecx,        ebx
    
    ; If the high word of b is zero, jump to the code to handle that special case [9]
    jz      .9
    
    ;---------------------------------------------------------------------------
    ; High word of b is known to be non-zero on this branch
    ;---------------------------------------------------------------------------
    
    ; Construct bhi, containing bits [ 1 + i : 32 + i ] of b
    ; Practically, this means that bhi is given by:
    ; bhi = ( high word of b ) << ( 31 - i ) | ( low word of b ) >> ( 1 + i )
    mov     eax,        [ esp  +16 ]
    shr     eax,        cl     
    shr     eax,        0x01
    not     ecx
    shl     ebx,        cl
    or      ebx,        eax
    
    ; Load the high and low words of a, and jump to [1] if the high word is
    ; larger than bhi to avoid overflowing the upcoming divide
    mov     edx,        [ esp + 12 ]
    mov     eax,        [ esp + 8 ]
    cmp     edx,        ebx
    jae     .1
    
    ;---------------------------------------------------------------------------
    ; High word of a is greater than or equal to ( b >> ( 1 + i ) ) on
    ; this branch
    ;---------------------------------------------------------------------------
    
    ; eax <-- qs, edx <-- r such that ahi : alo = bs * qs + r
    div     ebx
    
    push    edi
    not     ecx
    shr     eax,        0x01
    
    ; q = qs >> ( 1 + i )
    shr     eax,        cl
    mov     edi,        eax
    mov     ebx,        [ esp + 20 ]
    
    ; q * blo
    mul     ebx
    mov     ebx,        [ esp + 12 ]
    
    ; ECX : EBX = a
    mov     ecx,        [ esp + 16 ]
    sub     ebx,        eax
    
    ; ECX : EBX = a - q * blo
    sbb     ecx,        edx
    mov     eax,        [ esp + 24 ]
    
    ; q * bhi
    imul    eax,        edi
    
    ; ECX : EBX = a - q * b
    sub     ecx,        eax
    
    ; Decrement q if remainder is negative
    sbb     edi,        0x00
    xor     edx,        edx
    mov     eax,        edi
    pop     edi
    pop     ebx
    ret
    
    ;---------------------------------------------------------------------------
    ; High word of a is greater than or equal to ( b >> ( 1 + i ) ) on
    ; this branch
    ;---------------------------------------------------------------------------
    .1:
        
        ; Subtract bhi from ahi so that divide will not overflow, and find
        ; q and r such that:
        ; 
        ; ahi : alo = ( 1 : q) * bhi + r
        ; 
        ; Note that q is a number in ( 31 - i ).( 1 + i ) fix point
        sub     edx,        ebx
        div     ebx
        
        push    edi
        not     ecx
        shr     eax,        0x01
        or      eax,        0x80000000
        
        ; q = ( 1 : qs ) >> ( 1 + i )
        shr     eax,        cl
        mov     edi,        eax
        mov     ebx,        [ esp + 20 ]
        
        ; q * blo
        mul     ebx
        mov     ebx,        [ esp + 12 ]
        
        ; ECX : EBX = a
        mov     ecx,        [ esp + 16 ]
        sub     ebx,        eax
        
        ; ECX : EBX = a - q * blo
        sbb     ecx,        edx
        mov     eax,        [ esp + 24 ]
        
        ; q * bhi
        imul    eax,        edi
        
        ; ECX : EBX = a - q * b
        sub     ecx,        eax
        
        ; Decrement q if remainder is negative
        sbb     edi,        0x00
        xor     edx,        edx
        mov     eax,        edi
        pop     edi
        pop     ebx
        ret
        
    ;---------------------------------------------------------------------------
    ; High word of b is zero on this branch
    ;---------------------------------------------------------------------------
    .9:
        
        ; Find qhi and rhi such that:
        ; 
        ; ahi = qhi * b + rhi
        ; 
        ; With 0 ≤ rhi < b
        mov     eax,        [ esp + 12 ]
        mov     ecx,        [ esp + 16 ]
        xor     edx,        edx    
        div     ecx
        mov     ebx,        eax
        
        ; Find qlo such that:
        ; 
        ; rhi : alo = qlo * b + rlo  with 0 ≤ rlo < b
        ;
        ; And return qhi:qlo
        mov     eax,        [ esp + 8 ]
        div     ecx
        mov     edx,        ebx
        pop     ebx
        ret
    