# automatically generated by the FlatBuffers compiler, do not modify

# namespace: tflite

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class SliceOptions(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsSliceOptions(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = SliceOptions()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def SliceOptionsBufferHasIdentifier(cls, buf, offset, size_prefixed=False):
        return flatbuffers.util.BufferHasIdentifier(buf, offset, b"\x54\x46\x4C\x33", size_prefixed=size_prefixed)

    # SliceOptions
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

def SliceOptionsStart(builder): builder.StartObject(0)
def SliceOptionsEnd(builder): return builder.EndObject()
