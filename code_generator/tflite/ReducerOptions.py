# automatically generated by the FlatBuffers compiler, do not modify

# namespace: tflite

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class ReducerOptions(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsReducerOptions(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = ReducerOptions()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def ReducerOptionsBufferHasIdentifier(cls, buf, offset, size_prefixed=False):
        return flatbuffers.util.BufferHasIdentifier(buf, offset, b"\x54\x46\x4C\x33", size_prefixed=size_prefixed)

    # ReducerOptions
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # ReducerOptions
    def KeepDims(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return bool(self._tab.Get(flatbuffers.number_types.BoolFlags, o + self._tab.Pos))
        return False

def ReducerOptionsStart(builder): builder.StartObject(1)
def ReducerOptionsAddKeepDims(builder, keepDims): builder.PrependBoolSlot(0, keepDims, 0)
def ReducerOptionsEnd(builder): return builder.EndObject()
