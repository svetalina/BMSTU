global _strcopy
section .text

_strcopy:
    MOV RCX, RDX
    CMP RSI, RDI
    JE EXIT

    NOT_EQUAL:
        CMP RSI, RDI
        JG DIRECT_COPY

        MOV RAX, RDI
        SUB RAX, RSI

        CMP RAX, RCX
        JGE DIRECT_COPY

    REVERSE_COPY:
        ADD RDI, RCX
        DEC RDI
        ADD RSI, RCX
        DEC RSI

        STD

    DIRECT_COPY:
        REP MOVSB
        CLD

    EXIT:
        RET
